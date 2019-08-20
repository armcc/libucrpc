
#ifndef _COMPAT_H_
#define _COMPAT_H_

#define internal_function

#define attribute_hidden
#define attribute_noreturn
#define attribute_unused

#define libc_hidden_def(...)
#define libc_hidden_proto(...)

#define __set_errno(_val) errno = _val
#define __set_h_errno(_val) h_errno = _val

#endif
