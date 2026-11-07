#pragma once

#include <sstream>
#include <string>
#include "common_defs/source/IgniteMessage.h"

namespace Ignite {
	class model {
	public:
		static MTDataType GetType (const bool& value)
		{
			return MTDataType::BOOL;
		}
		static MTDataType GetType (const int8_t& value)
		{
			return MTDataType::INT8;
		}

		static MTDataType GetType (const uint8_t& value)
		{
			return MTDataType::UINT8;
		}

		static MTDataType GetType (const int16_t& value)
		{
			return MTDataType::INT16;
		}

		static MTDataType GetType (const uint16_t& value)
		{
			return MTDataType::UINT16;
		}

		static MTDataType GetType (const int32_t& value)
		{
			return MTDataType::INT32;
		}

		static MTDataType GetType (const uint32_t& value)
		{
			return MTDataType::UINT32;
		}

		static MTDataType GetType (const int64_t& value)
		{
			return MTDataType::INT64;
		}

		static MTDataType GetType (const uint64_t& value)
		{
			return MTDataType::UINT64;
		}

		static MTDataType GetType (const float& value)
		{
			return MTDataType::FLOAT32;
		}

		static MTDataType GetType (const std::string& value)
		{
			return MTDataType::STRING;
		}

		static const char* GetTypeName (MTDataType type)
		{
			static const char* typenames[] = { "bool", "u8", "i8", "u16", "i16", "u32", "i32", "u64", "i64", "float", "str" };
			return typenames[(uint8_t)type];
		}

		static std::string ToString (uint8_t value)
		{
			std::stringstream ss;
			ss << (int)(value);
			return ss.str ();
		}

		static std::string ToString (int8_t value)
		{
			std::stringstream ss;
			ss << (int)(value);
			return ss.str ();
		}

		template <typename T>
		static std::string ToString (T value)
		{
			std::stringstream ss;
			ss << value;
			return ss.str ();
		}
	};

	class AnyTypeBase {
	public:
		virtual ~AnyTypeBase () { }
		virtual bool operator<(const AnyTypeBase& rhs) = 0;
		virtual bool operator<=(const AnyTypeBase& rhs) = 0;
		virtual bool operator>(const AnyTypeBase& rhs) = 0;
		virtual bool operator>=(const AnyTypeBase& rhs) = 0;
		virtual bool operator==(const AnyTypeBase& rhs) = 0;
		virtual bool operator!=(const AnyTypeBase& rhs) = 0;
		virtual MTDataType GetType () const = 0;
		virtual std::string ToString () = 0;
		virtual const char* TypeName () const = 0;
	};

	template <typename T>
	class AnyTypeStore : public AnyTypeBase {
	public:
		AnyTypeStore (T value)
			: _data (value)
		{
		}

		AnyTypeStore () = default;
		AnyTypeBase& operator=(const AnyTypeBase& rhs)
		{
			if (this != &rhs) {
				if (rhs.GetType () == model::GetType (_data)) {
					const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
					_data = rhsvalue._data;
				}
			}
			return *this;
		}

		bool operator<(const AnyTypeBase& rhs) override
		{
			if (rhs.GetType () == model::GetType (_data)) {
				const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
				return _data < rhsvalue._data;
			}
			return false;
		}

		bool operator<=(const AnyTypeBase& rhs) override
		{
			if (rhs.GetType () == model::GetType (_data)) {
				const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
				return _data <= rhsvalue._data;
			}
			return false;
		}

		bool operator>(const AnyTypeBase& rhs) override
		{
			if (rhs.GetType () == model::GetType (_data)) {
				const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
				return _data > rhsvalue._data;
			}
			return false;
		}

		bool operator>=(const AnyTypeBase& rhs) override
		{
			if (rhs.GetType () == model::GetType (_data)) {
				const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
				return _data >= rhsvalue._data;
			}
			return false;
		}

		bool operator==(const AnyTypeBase& rhs) override
		{
			if (rhs.GetType () == model::GetType (_data)) {
				const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
				return _data == rhsvalue._data;
			}
			return false;
		}

		bool operator!=(const AnyTypeBase& rhs) override
		{
			if (rhs.GetType () == model::GetType (_data)) {
				const AnyTypeStore<T>& rhsvalue = (const AnyTypeStore<T>&)rhs;
				return _data != rhsvalue._data;
			}
			return false;
		}

		MTDataType GetType () const override
		{
			return model::GetType (_data);
		}

		std::string ToString () override
		{
			switch (GetType ()) {
				case MTDataType::INT8:
					return model::ToString (_data);
				case MTDataType::UINT8:
					return model::ToString (_data);
					break;
			}

			return model::ToString<T> (_data);
		}

		const char* TypeName () const override
		{
			return model::GetTypeName (GetType ());
		}
		T _data;
	};

	class AnyType {
	public:
		AnyType ()
			: _store (0)
		{
			_data = &_store;
		}

		AnyType (const MTDataType type)
		{
			switch (type) {
				case MTDataType::BOOL:
					_data = new (&_store) AnyTypeStore<bool> (0);
					break;
				case MTDataType::INT8:
					_data = new (&_store) AnyTypeStore<int8_t> (0);
					break;
				case MTDataType::UINT8:
					_data = new (&_store) AnyTypeStore<uint8_t> (0);
					break;
				case MTDataType::INT16:
					_data = new (&_store) AnyTypeStore<int16_t> (0);
					break;
				case MTDataType::UINT16:
					_data = new (&_store) AnyTypeStore<uint16_t> (0);
					break;
				case MTDataType::INT32:
					_data = new (&_store) AnyTypeStore<int32_t> (0);
					break;
				case MTDataType::UINT32:
					_data = new (&_store) AnyTypeStore<uint32_t> (0);
					break;
				case MTDataType::INT64:
					_data = new (&_store) AnyTypeStore<int64_t> (0);
					break;
				case MTDataType::UINT64:
					_data = new (&_store) AnyTypeStore<uint64_t> (0);
					break;
				case MTDataType::FLOAT32:
					_data = new (&_store) AnyTypeStore<float> (0);
					break;
				case MTDataType::STRING:
					_data = new AnyTypeStore<std::string> ("");
					break;
				default:
					break;
			}
		}

		AnyType (const AnyType& other)
		{
			if (other.GetType () == MTDataType::STRING) {
				_data = new AnyTypeStore<std::string> (other.get<std::string> ());
			}
			else {
				_store = other._store;
				_data = &_store;
			}
		}
		AnyType (const bool& value) { _data = new (&_store) AnyTypeStore<bool> (value); }
		AnyType (const int8_t& value) { _data = new (&_store) AnyTypeStore<int8_t> (value); }
		AnyType (const uint8_t& value) { _data = new (&_store) AnyTypeStore<uint8_t> (value); }
		AnyType (const int16_t& value) { _data = new (&_store) AnyTypeStore<int16_t> (value); }
		AnyType (const uint16_t& value) { _data = new (&_store) AnyTypeStore<uint16_t> (value); }
		AnyType (const int32_t& value) { _data = new (&_store) AnyTypeStore<int32_t> (value); }
		AnyType (const uint32_t& value) { _data = new (&_store) AnyTypeStore<uint32_t> (value); }
		AnyType (const int64_t& value) { _data = new (&_store) AnyTypeStore<int64_t> (value); }
		AnyType (const uint64_t& value) { _data = new (&_store) AnyTypeStore<uint64_t> (value); }
		AnyType (const float& value) { _data = new (&_store) AnyTypeStore<float> (value); }
		AnyType (const std::string& value) { _data = new AnyTypeStore<std::string> (value); }
		AnyType (const char* value) { _data = new AnyTypeStore<std::string> (value); }

		~AnyType ()
		{
			destroyData ();
		}
		MTDataType GetType () const { return _data->GetType (); }

		std::string ToString () const
		{
			return _data->ToString ();
		}

		const char* TypeName () const
		{
			return _data->TypeName ();
		}

		void destroyData ()
		{
			if (_data == &_store) {
				_data->~AnyTypeBase ();
			}
			else if (_data) {
				delete _data;
			}
			_data = nullptr;
		}

		AnyType& operator=(const AnyType& rhs)
		{
			if (this != &rhs) {
				//if (GetType() == rhs.GetType()) //TODO: check to be corrected? Aman
				{
					if (rhs.GetType () == MTDataType::STRING) {
						if (GetType () == MTDataType::STRING && _data) {
							delete (_data);
						}
						_data = new AnyTypeStore<std::string> (rhs.get<std::string> ());
					}
					else {
						_store = rhs._store;
						_data = &_store;
					}
				}
			}
			return *this;
		}

		template <typename T>
		const T& get () const
		{
			auto typed = (AnyTypeStore<T>*)_data;
			return typed->_data;
		}

		template <typename T>
		void set (const T& value)
		{
			MTDataType type = model::GetType (value);

			if (GetType () == type) {
				auto typed = (AnyTypeStore<T>*)_data;
				typed->_data = value;
			}
			else {
				destroyData ();
				switch (type) {
					case MTDataType::BOOL:
					case MTDataType::INT8:
					case MTDataType::UINT8:
					case MTDataType::INT16:
					case MTDataType::UINT16:
					case MTDataType::INT32:
					case MTDataType::UINT32:
					case MTDataType::INT64:
					case MTDataType::UINT64:
					case MTDataType::FLOAT32: {
						_data = new (&_store) AnyTypeStore<T> (value);
					} break;
					default: {
						_data = new AnyTypeStore<T> (value);
					} break;
				}
			}
		}
		bool operator<(AnyType& rhs) { return (*_data) < (*rhs._data); }
		bool operator<=(AnyType& rhs) { return (*_data) <= (*rhs._data); }
		bool operator>(AnyType& rhs) { return (*_data) > (*rhs._data); }
		bool operator>=(AnyType& rhs) { return (*_data) >= (*rhs._data); }
		bool operator==(AnyType& rhs) { return (*_data) == (*rhs._data); }
		bool operator!=(AnyType& rhs) { return (*_data) != (*rhs._data); }

	private:
		AnyTypeBase* _data;
		AnyTypeStore<uint64_t> _store;
	};
}
