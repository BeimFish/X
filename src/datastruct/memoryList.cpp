#include"memoryList.h"



void memoryList::init(void* sptr, _u32 size, _u32 id)
{

	start.next = &end;
	//start.next指向end指针
	start.id = id;
	//start.id指向该内存的管理对象id

	start.size = 0;      
	//start数据域为0
	start.sptr = (_ptrSize)sptr;                             
	//start的数据域起始地址，也是堆内存起始地址
	start.token = 0;
	//设置start为非共享内存块

	end.next = nullptr;
	//end.next悬空，nullptr用于结束判断
	end.id = size;                                                      
	//end.id保存当前堆余量（剩余堆内存）

	end.size = 0;                                                     
	//end数据域为0
	end.sptr = start.sptr + size + sizeof(memoryEntry);            
	//end数据域的起始地址，比堆内存大一个head长度：堆内存起始地址 + 堆内存容量大小 + head长度
	end.token = 0;
	//设置end为非共享内存块
}
/*
* sptr:堆内存的起始地址
* size:堆内存的总长度大小
* id:堆内存管理者id
*/

void* memoryList::createEntry(_u32 size, _u32 id, _u8 token)
{
	memoryEntry* ptr = &start;
	//临时指针指向start指针

	for (;;)
	{
		if ((size + sizeof(memoryEntry)) <= (ptr->next->sptr - sizeof(memoryEntry) - ptr->sptr - ptr->size))
		{	//1.即将插入内存块的长度 = 当前申请内存数据域的容量大小 + head容量大小
			//2.当前指向内存块与后方相邻内存块之间的空域内存块长度：大小当前指向内存块指向的下一个内存块的数据域起始地址 -
			// head长度 - 当前按内存块数据域起始地址 - 当前内存块的数据域长度
			//待插入内存块长度<=当前内存块与后方相邻内存块之间的空余内存块长度 ->两内存块之间可分配内存（否则查询下一块内存与后续内存）
		



			memoryEntry* t = (memoryEntry*)(ptr->sptr + ptr->size);
			//在当前指向内存块的数据域末尾创建新内存块的head
			t->id = id;
			//设置新内存块的所属对象id

			t->next = ptr->next;
			//新内存块的next指向当前内存块的下一块内存
			ptr->next = t;
			//当前内存块的后方插入新内存块
		
			t->sptr = (_ptrSize)t + sizeof(memoryEntry);
			//新内存块的sptr指向该内存块数据域的起始地址
			t->size = size;
			//设置新内存块数据域的长度
			t->token = token;
			//设置新内存块的标识符（0标识符是非共享标识）
			end.id = end.id - sizeof(memoryEntry) - size;
			//堆内存剩余空间 = 堆内存剩余空间中 - 插入新内存块所占用的所需空间大小
			return (void*)t->sptr;
			//返回新内存块的数据域起始地址

		}
		else
		{
			if (ptr->next->next == nullptr) return nullptr;
			//如果下一个内存块没有后续内存块，遍历结束，当前堆内存中不存在符合要求的内存块
			ptr = ptr->next;
			//将遍历指针ptr指向下一个内存块
		}
	}
}
/*
* size:申请内存块的长度（仅数据域，不包括head区域长度）
* id:该内存块的申请进程id
*/

void* memoryList::getShare(_u32 token)
{
	memoryEntry* ptr = &start;
	//临时指针指向start指针

	for (;;)
	{
		if (ptr->next->next != nullptr)
		{
			//保证当前块后至少存在两个内存块：检查下一个内存块是否是end块（当前->end->nullptr）
			//如果存在未检查的非end内存块，则进入该分支

			if (ptr->next->token == token)
			{
				//判断下一个内存块的token是否是需要的内存块，如果是，进入该分支

				return (void*)ptr->next->sptr;
				//返回该内存地址
			}
			else
			{
				ptr = ptr->next;
				//如果不是，将临时指针指向后一个内存块
				//这个内存块一定不是end块，上一个检查保证了最少存在三个块（start-＞m-＞end）
				//就算后移一位，该内存块绝不是end
			}
		}
		else
		{
			//检查下一个内存块是否是end块（当前->end->nullptr）
			//下一块为end，结束检查
			return nullptr;
		}
	}
}
/*
* 根据token找到共享内存块
*/

void memoryList::deleteEntry(void* dptr)
{
	memoryEntry* ptr = &start;
	//临时指针指向start指针

	for (;;)
	{
		if (ptr->next->next != nullptr)
		{
			//检查下一个内存块是否是end块（当前->end->nullptr）
			//如果存在未检查的非end内存块，则进入该分支

			if (ptr->next->sptr == (_ptrSize)dptr)
			{
				//判断下一个内存块是否是需要删除的内存块，如果是，进入该分支

				end.id = end.id + sizeof(memoryEntry) + ptr->next->size;
				//更新堆内存剩余长度：将所需删除的内存块长度加回

				ptr->next = ptr->next->next;
				//绕过下一个内存块，把当前内存块的next连接到下下个内存块
				return;
				//删除结束，不再检查后续内存块
			}
			else
			{
				ptr = ptr->next;
				//如果不是，将临时指针指向后一个内存块
				//这个内存块一定不是end块，上一个检查保证了最少存在三个块（start-＞m-＞end）
				//就算后移一位，该内存块绝不是end
			}
		}
		else
		{
			//检查下一个内存块是否是end块（当前->end->nullptr）
			//下一块为end，结束检查
			return;
		}
	}
}
/*
* 根据地址删除对应内存块
* dptr:待删除内存的数据域地址
*/

void memoryList::deleteEntry(_u32 id)
{
	memoryEntry* ptr = &start;
	//临时指针指向start指针

	for (;;)
	{
		if (ptr->next->next != nullptr)
		{
			//保证当前块后至少存在两个内存块：检查下一个内存块是否是end块（当前->end->nullptr）
			//如果存在未检查的非end内存块，则进入该分支

			if (ptr->next->id == id)
			{
				//判断下一个内存块的所属id是否是需要删除的内存块，如果是，进入该分支

				end.id = end.id + sizeof(memoryEntry) + ptr->next->size;
				//更新堆内存剩余长度：将所需删除的内存块长度加回
				ptr->next = ptr->next->next;
				//绕过下一个内存块，把当前内存块的next连接到下下个内存块
			}
			else
			{
				ptr = ptr->next;
				//如果不是，将临时指针指向后一个内存块
				//这个内存块一定不是end块，上一个检查保证了最少存在三个块（start-＞m-＞end）
				//就算后移一位，该内存块绝不是end
			}
		}
		else
		{
			//检查下一个内存块是否是end块（当前->end->nullptr）
			//下一块为end，结束检查
			return;
		}
	}
}
/*
* 根据id删除所有对应的内存块
* id:待删除内存的所属id
* 后续添加掩码，删除所有线程资源！！！！！！！！！！！！！1
*/
