/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_module.h
 * \brief kernel module operation.
 * \author Zhidao
 */

#ifndef __LIW_MODULE_H__
#define __LIW_MODULE_H__

#ifdef __KERNEL__
/* Linux kernel space programming */
# ifndef MODULE
# define MODULE
# endif /* MODULE */
# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/slab.h>
 /* initializer and terminator */
# if LINUX_VERSION_CODE > 0x020404
# define MODULE_INIT(f) \
  static int f(void);\
  module_init(f);\
  int __init f(void)
# define MODULE_EXIT(f) \
  static void f(void);\
  module_exit(f);\
  void __exit f(void)
# endif /* LINUX_VERSION_CODE */
# define calloc(s,n) kmalloc( (s)*(n), GFP_KERNEL )
# define free(m)     kfree(m)
#endif /* __KERNEL__ */

#endif /* __LIW_MODULE_H__ */
