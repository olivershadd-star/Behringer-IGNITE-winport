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

#pragma once

#define JIF_FORMAT_LOADER_LZW_CODE_TABLE_EMPTY -2
#define JIF_FORMAT_LOADER_END_OF_CODE_STREAM -1
#define READ_DATA_BLOCK_ERROR -1

namespace jif 
{
    struct Image 
    {
        Image() :image(), x(0), y(0), width(0), height(0)
        {
        }
        Image(const juce::Image&& img) :image(img), x(0), y(0), width(img.getWidth()),
            height(img.getHeight())
        {
        }
        void paint(juce::Graphics& g, const juce::Rectangle<float>& bounds);
        juce::Image image;
        int x, y, width, height;
    };
    class Format
    {
        struct Loader
        {
            Loader(juce::InputStream& in);
            bool readHeader();
            void loadAnotherImage();
            Image loaderImage;
        private:
            juce::InputStream& input;
            juce::uint8 buffer[260];
            juce::uint8 buf[16];
            juce::PixelARGB palette[256];
            bool dataBlockIsZero, fresh, finished;
            int imageWidth, imageHeight, transparent, numColours;
            int currentBit, lastBit, lastByteIndex;
            int codeSize, setCodeSize;
            int maxCode, maxCodeSize;
            int firstcode, oldcode;
            int clearCode, endCode;
            enum { maxGifCode = 1 << 12 };
            int table[2][maxGifCode];
            int stack[2 * maxGifCode];
            int* sp;
            bool getSizeFromHeader();
            bool readPalette(const int numCols);
            int readDataBlock(juce::uint8* const dest);
            int readExtension();
            void clearTable();
            void initialise(const int inputCodeSize);
            int readLZWByte();
            int getCode(const int codeSize_, const bool shouldInitialise);
            bool readImage(const int interlace, const int transparent);
            JUCE_DECLARE_NON_COPYABLE(Loader)
        };
    public:
        bool valid(juce::InputStream& in) 
        {
#if (JUCE_MAC || JUCE_IOS) && USE_COREGRAPHICS_RENDERING && JUCE_USE_COREIMAGE_LOADER
            return false;
#else
            loader = std::make_unique<Loader>(in);
            return loader->readHeader();
#endif
        }
        Image decodeImage() 
        {
            loader->loadAnotherImage();
            return loader->loaderImage;
        };
        std::unique_ptr<Loader> loader;
    };

    struct JIF 
    {
        JIF() :images(),readIdx(0)
        {
        }
        JIF(const void* jifData, const size_t jifSize);
        void addImg(const Image& img) { images.push_back(img); }
        const size_t numImages() const noexcept { return images.size(); }
        void init();
        void paint(juce::Graphics& g, const juce::Rectangle<float>& bounds);
        void operator++() { ++readIdx; }
        void resetAnimation() { readIdx = 0; }
        std::vector<Image> images;
        int readIdx;
    };
}

namespace ui
{
    class IgniteGifPreloader : public juce::Component, private Timer
    {
    public:
        IgniteGifPreloader();
        IgniteGifPreloader(int Width, int Height);
        ~IgniteGifPreloader() override;
        void paint(juce::Graphics&) override;
        void resized() override;
        void show();
        void setProgressStatus( String message);

        CommonPopUp* popupPtr = nullptr;

        jif::JIF jifobject;
        static IgniteGifPreloader* GetGifInstance()
        {
            static IgniteGifPreloader* getInstance;
            if (NULL == getInstance)
            {
                getInstance = new IgniteGifPreloader();
            }
            return getInstance;
        }

    private:
        juce::Component::SafePointer<juce::DialogWindow> dialogWindow;
        std::unique_ptr<Viewport> view;
        Viewport infoViewPort;
        int width{ 0 }, height{ 0 };
        int availableHeightForViewPort = 0;
        int requiredHeight = 0;
        CommonLabel infoLabel1{ "" };
        juce::Image loadedGifImage;
       
        void setGifTimeinMs(int ms);
        void setGifVisible(bool status);
        void timerCallback() override;
      
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteGifPreloader)
    };
};