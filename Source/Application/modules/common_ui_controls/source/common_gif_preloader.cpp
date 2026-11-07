
/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
 * This file is part of IGNITE.
 *
 * IGNITE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

namespace jif
{
    void jif::Image::paint(juce::Graphics& g, const juce::Rectangle<float>& bounds)
    {
        const auto nX = x * bounds.getWidth() + 220;
        const auto nY = y * bounds.getHeight() + 20;
        const auto nWidth = width * (bounds.getWidth());
        const auto nHeight = height * (bounds.getHeight());
        g.drawImage(image, { nX, nY, nWidth, nHeight });
    }

    jif::Format::Loader::Loader(juce::InputStream& in) : input(in), lastByteIndex(0)
    {
    }

    bool jif::Format::Loader::readHeader()
    {
        if (!getSizeFromHeader())
            return false;
        if (input.read(buf, 3) != 3)
            return false;
        numColours = 2 << (buf[0] & 7);
        if ((buf[0] & 0x80) == 0)                //checking whether the GIF image has a global color table or not.
            return false;
        readPalette(numColours);
        return true;
    }

    void jif::Format::Loader::loadAnotherImage()
    {
        for (;;)
        {
            if (input.read(buf, 1) != 1 || buf[0] == ';')  // checking if the first byte of the buf is a semicolon if yes, the loop will terminate.
                break;
            if (buf[0] == '!')                        //this  will check for the gif extensions & skip over any GIF extensions that it does not understand
            {
                if (readExtension())
                    continue;
                break;
            }
            if (buf[0] != ',')        //checking first byte of the buf is comma or not 
                continue;
            if (input.read(buf, 9) == 9)
            {
                const auto imageX = (int)juce::ByteOrder::littleEndianShort(buf + 0);
                const auto imageY = (int)juce::ByteOrder::littleEndianShort(buf + 2);
                imageWidth = (int)juce::ByteOrder::littleEndianShort(buf + 4);
                imageHeight = (int)juce::ByteOrder::littleEndianShort(buf + 6);
                numColours = 2 << (buf[8] & 7);
                if ((buf[8] & 0x80) != 0)                    //checking whether the GIF image has a global color table or not.
                    if (!readPalette(numColours))
                        break;
                const auto pxlFormat = transparent >= 0 ? juce::Image::ARGB : juce::Image::RGB;
                loaderImage = juce::Image(pxlFormat, imageWidth, imageHeight, transparent >= 0);
                loaderImage.x = imageX;
                loaderImage.y = imageY;
                loaderImage.image.getProperties()->set("originalImageHadAlpha", transparent >= 0);
                readImage((buf[8] & 0x40) != 0, transparent);      //whether the GIF image has a local color table or not.
            }
            break;
        }
    }

    bool jif::Format::Loader::getSizeFromHeader()
    {
        char b[6];
        if (input.read(b, 6) == 6
            && (strncmp("GIF87a", b, 6) == 0           // GIF87a is the original version of the GIF image format. 
                || strncmp("GIF89a", b, 6) == 0))      //GIF89a is an extension of the GIF87a image format.
        {
            if (input.read(b, 4) == 4)
            {
                imageWidth = (int)juce::ByteOrder::littleEndianShort(b);
                imageHeight = (int)juce::ByteOrder::littleEndianShort(b + 2);
                return ((imageWidth > 0) && (imageHeight > 0));
            }
        }
        return false;
    }

    bool jif::Format::Loader::readPalette(const int numCols)
    {
        for (int i = 0; i < numCols; ++i)
        {
            juce::uint8 rgb[4];
            input.read(rgb, 3);
            palette[i].setARGB(0xff, rgb[0], rgb[1], rgb[2]);
            palette[i].premultiply();
        }
        return true;                     //returns true if the palette was successfully read if not false
    }

    int jif::Format::Loader::readDataBlock(juce::uint8* const dest)
    {
        juce::uint8 n;
        if (input.read(&n, 1) == 1)
        {
            dataBlockIsZero = (n == 0);

            if (dataBlockIsZero || (input.read(dest, n) == n))
                return n;
        }
        return READ_DATA_BLOCK_ERROR;
    }

    int jif::Format::Loader::readExtension()
    {
        juce::uint8 type;
        if (input.read(&type, 1) != 1)
            return false;
        juce::uint8 b[260];
        int n = 0;

        if (type == 0xf9)      // check if the current extension is a GIF Comment Extension. 
        {
            n = readDataBlock(b);
            if (n < 0)
                return 1;

            if ((b[0] & 1) != 0)
                transparent = b[3];
        }
        do
        {
            n = readDataBlock(b);
        } while (n > 0);
       return (n >= 0);
    }

    void jif::Format::Loader::clearTable()
    {
        int i;
        for (i = 0; i < clearCode; ++i)
        {
            table[0][i] = 0;
            table[1][i] = i;
        }
        for (; i < maxGifCode; ++i)
        {
            table[0][i] = 0;
            table[1][i] = 0;
        }
    }

    void jif::Format::Loader::initialise(const int inputCodeSize)
    {
        setCodeSize = inputCodeSize;
        codeSize = setCodeSize + 1;
        clearCode = 1 << setCodeSize;
        endCode = clearCode + 1;
        maxCodeSize = 2 * clearCode;
        maxCode = clearCode + 2;
        getCode(0, true);
        fresh = true;
        clearTable();
        sp = stack;
    }

    int jif::Format::Loader::readLZWByte()
    {
        if (fresh)
        {
            fresh = false;
            for (;;)
            {
                firstcode = oldcode = getCode(codeSize, false);
                if (firstcode != clearCode)
                    return firstcode;
            }
        }
        if (sp > stack)
            return *(--sp);

        int code;
        while ((code = getCode(codeSize, false)) >= 0)
        {
            if (code == clearCode)
            {
                clearTable();
                codeSize = setCodeSize + 1;
                maxCodeSize = 2 * clearCode;
                maxCode = clearCode + 2;
                sp = stack;
                firstcode = oldcode = getCode(codeSize, false);
                return firstcode;
            }
            else if (code == endCode)
            {
                if (dataBlockIsZero)
                    return JIF_FORMAT_LOADER_LZW_CODE_TABLE_EMPTY;
                //juce::uint8 buf[260];//TODO remove after test
                int n;
                while ((n = readDataBlock(buf)) > 0)
                {
                }
                if (n != 0)
                    return JIF_FORMAT_LOADER_LZW_CODE_TABLE_EMPTY;
            }
            const int incode = code;
            if (code >= maxCode)
            {
                *sp++ = firstcode;
                code = oldcode;
            }
            while (code >= clearCode)
            {
                *sp++ = table[1][code];
                if (code == table[0][code])
                    return JIF_FORMAT_LOADER_LZW_CODE_TABLE_EMPTY;

                code = table[0][code];
            }
            *sp++ = firstcode = table[1][code];

            if ((code = maxCode) < maxGifCode)
            {
                table[0][code] = oldcode;
                table[1][code] = firstcode;
                ++maxCode;
                if (maxCode >= maxCodeSize && maxCodeSize < maxGifCode)
                {
                    maxCodeSize <<= 1;
                    ++codeSize;
                }
            }
            oldcode = incode;
            if (sp > stack)
                return *(--sp);
        }
        return code;
    }

    int jif::Format::Loader::getCode(const int codeSize_, const bool shouldInitialise)
    {
        if (shouldInitialise)
        {
            currentBit = 0;
            lastBit = 0;
            finished = false;
            return 0;
        }

        if ((currentBit + codeSize_) >= lastBit)
        {
            if (finished)
                return JIF_FORMAT_LOADER_END_OF_CODE_STREAM;
            buffer[0] = buffer[lastByteIndex - 2];
            buffer[1] = buffer[lastByteIndex - 1];
            const int n = readDataBlock(buffer + 2);
            if (n == 0)
                finished = true;
            lastByteIndex = 2 + n;
            currentBit = (currentBit - lastBit) + 16;
            lastBit = (2 + n) * 8;
        }
        int result = 0;
        int i = currentBit;
        for (int j = 0; j < codeSize_; ++j)
        {
            result |= ((buffer[i >> 3] & (1 << (i & 7))) != 0) << j;
            ++i;
        }
        currentBit += codeSize_;
        return result;
    }

    bool jif::Format::Loader::readImage(const int interlace, const int _transparent)
    {
        juce::uint8 c;
        if (input.read(&c, 1) != 1)
            return false;
        initialise(c);
        if (_transparent >= 0)
            palette[_transparent].setARGB(0, 0, 0, 0);
        int xpos = 0, ypos = 0, yStep = 8, pass = 0;
        const juce::Image::BitmapData destData(loaderImage.image, juce::Image::BitmapData::writeOnly);
        juce::uint8* p = destData.getPixelPointer(0, 0);
        const bool hasAlpha = loaderImage.image.hasAlphaChannel();
        for (;;)
        {
            const int index = readLZWByte();
            if (index < 0)
                break;
            if (hasAlpha)
                ((juce::PixelARGB*)p)->set(palette[index]);
            else
                ((juce::PixelRGB*)p)->set(palette[index]);
            p += destData.pixelStride;
            if (++xpos == destData.width)
            {
                xpos = 0;
                if (interlace)
                {
                    ypos += yStep;
                    while (ypos >= destData.height)
                    {
                        switch (++pass)
                        {
                        case 1:     ypos = 4; yStep = 8; break;
                        case 2:     ypos = 2; yStep = 4; break;
                        case 3:     ypos = 1; yStep = 2; break;
                        default:    return true;
                        }
                    }
                }
                else
                {
                    if (++ypos >= destData.height)
                        break;
                }
                p = destData.getPixelPointer(xpos, ypos);
            }
        }
        return true;
    }

    void jif::JIF::paint(juce::Graphics& g, const juce::Rectangle<float>& bounds)
    {
        g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);
        if (readIdx >= numImages())
        {
            readIdx = 0;
        }
        images[readIdx].paint(g, bounds);
    }

    void jif::JIF::init()
    {
        auto maxWidth = 0;
        auto maxHeight = 0;
        for (auto& img : images)
        {
            const auto w = img.image.getWidth();
            const auto h = img.image.getHeight();
            maxWidth = maxWidth < w ? w : maxWidth;
            maxHeight = maxHeight < h ? h : maxHeight;
        }
        for (auto& img : images)
        {
            img.x /= maxWidth;
            img.y /= maxHeight;
            img.width /= maxWidth;
            img.height /= maxHeight;
        }
    }

    jif::JIF::JIF(const void* jifData, const size_t jifSize) :
        images(),
        readIdx(0)
    {
        juce::MemoryInputStream memoryInputStream(jifData, jifSize, true);
        Format format;
        if (format.valid(memoryInputStream))
            while (!memoryInputStream.isExhausted())
            {
                const auto img = format.decodeImage();
                if (img.image.isValid())
                    addImg(img);
            }
        init();
    }
};

namespace ui
{

    IgniteGifPreloader::IgniteGifPreloader()
    {
    }

    IgniteGifPreloader::IgniteGifPreloader(int Width, int Height) :jifobject(BinaryData::preloader3_gif, BinaryData::preloader3_gifSize)
    {
        width = Width;
        height = Height;
        setSize(Width, Height);
        infoLabel1.makeVisible(this);
        
        juce::File appDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getParentDirectory();
        juce::File gifFile = appDir.getChildFile("preloader3.gif");
        juce::FileInputStream gifInputStream(gifFile);
        loadedGifImage = juce::ImageFileFormat::loadFrom(gifFile);
    }

    IgniteGifPreloader ::~IgniteGifPreloader()
    {
        delete dialogWindow;
    }

    void IgniteGifPreloader::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds();
        jifobject.paint(g, juce::Rectangle <float>{ (float)bounds.getX(), (float)bounds.getY(), ((float)bounds.getWidth()-450), ((float)bounds.getHeight()-140)});
    }

    void IgniteGifPreloader::resized()
    {
        infoLabel1.setBounds(140, 180, 400, 40);
    }

    void IgniteGifPreloader::timerCallback() 
    {
        ++jifobject;
        repaint();
    }

    void IgniteGifPreloader::setGifTimeinMs(int ms)
    {
        startTimer(ms);
    }

    void IgniteGifPreloader::setGifVisible(bool status)
    {
        this->setVisible(status);
        if (status)
            setGifTimeinMs(50);
        else
        {
            stopTimer();
        }
    }

    void IgniteGifPreloader::show()
    {
        std::function<void(int)> CallbackOnExit;
        view.reset(new CommonViewport());
        setGifTimeinMs(50);
        CommonUtils::showCustomDialog("Copy", this, [this, CallbackOnExit](int r) {
            if (CallbackOnExit)
                CallbackOnExit(r);

            view.reset();
        }, ui::Rectangle<int>{0, 0, width, height}, false);
    }

    void IgniteGifPreloader::setProgressStatus(String message)
    {
        infoLabel1.setText(message, dontSendNotification);
    }
};