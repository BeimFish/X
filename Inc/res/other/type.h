typedef signed char        _i8;
typedef short              _i16;
typedef int                _i32;
typedef long long          _i64;
typedef unsigned char      _u8;
typedef unsigned short     _u16;
typedef unsigned int       _u32;
typedef unsigned long long _u64;




typedef _u64 _ptrSize;
typedef _u32 _acptSize;
/*               ACPT规则
* A内核类型：4  （28-31）       0：通用，1：CM4，2：CM7
* C 内核ID ：4  （24-27）      16内核
* P 进程ID ：20 （4-23）
* T 线程ID ：4  （0-3）
*/
