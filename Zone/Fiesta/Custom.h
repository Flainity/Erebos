#pragma once

namespace Fiesta::Custom
{
	struct _Container_base12;
	struct _Container_proxy;

	struct _Container_base0
	{
	};

	template<typename S>
	struct _Allocator_base
	{
	};

	template<typename S>
	struct allocator : _Allocator_base<S>
	{
	};

	template<typename S, typename T, typename U>
	struct binary_function
	{
	};

	template<typename S>
	struct less : binary_function<S, S, bool>
	{
	};

#pragma pack(push, 4)
	template<typename S, typename T>
	struct _List_nod : _Container_base0
	{
		struct _Node
		{
			_Node* _Next;
			_Node* _Prev;
			S _Myval;
		};

		_Node* _Myhead;
		unsigned int _Mysize;
		allocator<_Node> _Alnod;
		T _Alval;
	};
#pragma pack(pop)

	template<typename S, typename T>
	struct _List_val : _List_nod<S, T>
	{
	};

	template<typename S, typename T>
	struct list : _List_val<S, T>
	{
	};

	template<typename S, typename T, typename U, typename V>
	struct _Tset_traits : _Container_base0
	{
		T comp;
	};

#pragma pack(push, 4)
	template<class T>
	struct _Tree_nod : _Tset_traits<void*, less<void*>, void*, void*>
	{

		struct _Node
		{
			_Node* _Left;
			_Node* _Parent;
			_Node* _Right;
			void* _Myval;
			char _Color;
			char _Isnil;
		};

		_Node* _Myhead;
		unsigned int _Mysize;
		allocator<_Node> _Alnod;
		allocator<void*> _Alval;
	};
#pragma pack(pop)

	template<typename S>
	struct _Tree_val : _Tree_nod<S>
	{
	};

	template<typename S>
	struct _Tree : _Tree_val<S>
	{
	};

	template<typename S, typename T, typename U>
	struct set : _Tree<_Tset_traits<S, T, U, int>>
	{
	};

#pragma pack(push, 4)
	template<typename S, typename T>
	struct _Vector_val : _Container_base0
	{
		S* _Myfirst;
		S* _Mylast;
		S* _Myend;
		T _Alval;
	};
#pragma pack(pop)

	template<typename S, typename T>
	struct vector : _Vector_val<S, T>
	{
	};

	template<typename S>
	struct char_traits
	{
	};

#pragma pack(push, 4)
	template <typename S, typename T>
	struct _String_val : _Container_base0
	{
		union _Bxty
		{
			S _Buf[16];
			S* _Ptr;
			S _Alias[16];
		};

		_Bxty _Bx;
		unsigned int _Mysize;
		unsigned int _Myres;
		T _Alval;
	};
#pragma pack(pop)

	template <typename S, typename T, typename U>
	struct basic_string : _String_val<S, U>
	{
	};

	struct string : basic_string<char, char_traits<char>, allocator<char>>
	{
	};

	struct _Iterator_base12
	{
		_Container_proxy* _Myproxy;
		_Iterator_base12* _Mynextiter;
	};


	struct _Container_proxy
	{
		_Container_base12* _Mycont;
		_Iterator_base12* _Myfirstiter;
	};


	struct _Container_base12
	{
		_Container_proxy* _Myproxy;
	};

#pragma pack(push, 4)
	template<typename S, typename T>
	struct _Deque_val : _Container_base12
	{
		S** _Map;
		unsigned int _Mapsize;
		unsigned int _Myoff;
		unsigned int _Mysize;
		T _Alval;
		allocator<S*> _Almap;
	};
#pragma pack(pop)

	template<typename S, typename T>
	struct deque : _Deque_val<S, T>
	{
	};

	template<typename S, typename T>
	struct _Pair_base
	{
		S first;
		T second;
	};

	template<typename S, typename T>
	struct pair : _Pair_base<S, T>
	{
	};
}

namespace Fiesta::CustomExtension
{
	template<typename S, typename T, typename U, typename V>
	struct hash_map
	{
		int unk[11];
	};

	template<typename S, typename T, typename U, typename V>
	struct hash_multimap
	{
		int unk[11];
	};

	template<typename S, typename T>
	struct hash_compare
	{
	};
}