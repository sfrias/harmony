#ifndef _arch_h_included_
#define _arch_h_included_

/*!
 * @file arch.h
 *
 * @brief Global project definitions for name, version, copyright,
 * license, global configuration, and architectural features.
 *
 * Derive specific architectural definitions from configuration
 * parameters set up in @link config/config.h config.h@endlink and
 * present them for normative use by the compiler.  Also global
 * constant strings for several purposes.
 *
 * Define critical symbols as tested below.
 * This is done by the @link ./config.sh config.sh@endlink script.
 *
 * <b>DO NOT FORGET</b> to use the GCC options found
 * in @b ../config/confopts.gcc on the GCC command
 * line!  This can be done as,
 * @verbatim

       $ gcc `cat ../config/config_opts_always.gcc` \
             `cat ../config/config_opts_usually.gcc` \
             -otheropts -c filename.c ...
  
       $ gcc `cat ../config/config_opts_always.gccld` \
             ... *.o -o targetbinary

   @endverbatim
 *
 * @todo There needs to be a Java equivalent written for the
 *       macros @link ##ARCH_COPYRIGHT_TEXT_APACHE
         ARCH_COPYRIGHT_TEXT_APACHE@endlink, @link
         #ARCH_LICENSE_TEXT_APACHE ARCH_LICENSE_TEXT_APACHE@endlink,
 *      and @link #ARCH_COPYRIGHT_APACHE ARCH_COPYRIGHT_APACHE()@endlink
 *
 * @section Control
 *
 * \$URL$ \$Id$
 *
 * Copyright 2005 The Apache Software Foundation
 * or its licensors, as applicable.
 *
 * Licensed under the Apache License, Version 2.0 ("the License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * @version \$LastChangedRevision$
 *
 * @date \$LastChangedDate$
 *
 * @author \$LastChangedBy$
 *         Original code contributed by Daniel Lydick on 09/28/2005.
 *
 * @section Reference
 *
 */


/*!
 * @def ARCH_COPYRIGHT_TEXT_APACHE
 *
 * @brief Copyright declaration string for the Apache Software
 * Foundation for all files in program.
 *
 */

#define ARCH_COPYRIGHT_TEXT_APACHE \
"Copyright 2005 The Apache Software Foundation or its licensors, as applicable."


/*!
 * @def ARCH_LICENSE_TEXT_APACHE
 *
 * @brief License declaration string for the Apache Software
 * Foundation for all files in program.
 *
 */

#define ARCH_LICENSE_TEXT_APACHE \
"Licensed under the Apache License, Version 2.0 (\"the License\");\n\
you may not use this file except in compliance with the License.\n\
You may obtain a copy of the License at\n\
\n\
    http://www.apache.org/licenses/LICENSE-2.0\n\
\n\
Unless required by applicable law or agreed to in writing,\n\
software distributed under the License is distributed on an\n\
\"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,\n\
either express or implied.\n\
\n\
See the License for the specific language governing permissions\n\
and limitations under the License."


/*!
 * @def ARCH_COPYRIGHT_APACHE()
 *
 * @brief Copyright declaration macro for the Apache Software Foundation
 * for all files in program.
 *
 * This macro declares the copyright by the Apache Software Foundation
 * for all source files.
 *
 * Declare a static string containing SVN info plus copyright and
 * declare a static function that references the string, plus a
 * local that recursively calls the function.  This function is
 * used to satisfy the compiler that the static string is being
 * referenced without also generating a similar message about the
 * static function not being referenced.
 *
 * @param filetoken   Any string that, when concatenated with an
 *                    underscore (_) and the @p @b exttoken parameter,
 *                    forms a globally unique combination.  This
 *                    is typically the file name itself without
 *                    the file extension name, unquoted.
 *
 * @param exttoken    Any string that, when the @p @b filetoken
 *                    parameter and an underscore (_) are concatenated
 *                    before it, forms a globally unique combination.
 *                    This is typically the file extension name itself
 *                    without the file name, unquoted.
 *
 * @param svnidstring Source code management token representing
 *                    as much information about the file as is
 *                    desired to insert into the static copyright
 *                    string for each source file and header file.
 *                    For RCS and CVS systems, this would typically
 *                    be the <b>@$<code>Header:</code> @$</b> token,
 *                    in double quotes.  As currently managed in
 *                    the Apache SVN repository, it contains the string
 *       &quot;<b>@$<code>URL:</code> @$ @$<code>Id:</code> @$</b>&quot;
 *
 *
 * @returns @link #rvoid rvoid@endlink
 *
 *
 * @internal The @c @b svnidstring parameter contains highly mangled
 *           source code control keyword strings.  They are mangled so
 *           as to hide them from version control substitution, yet
 *           display in the compiled documentation correctly.
 *
 * @internal The initial ASCII \\0 (NUL) character is inserted to
 *           guarantee that the string itself will @e never be
 *           appended to some previous text-type data, thus not
 *           being the beginning of a string for search purposes
 *           in the output (binary) form of the file invoking the macro.
 *           Refer to @link ./getsvndata.sh getsvndata.sh@endlink
 *           for more information.
 *
 */

#define ARCH_COPYRIGHT_APACHE(filetoken, exttoken, svnidstring)    \
static char *filetoken##_##exttoken##_copyright = "\0" svnidstring \
" " ARCH_COPYRIGHT_TEXT_APACHE;                                    \
                                                                   \
static void filetoken##_##exttoken##_dummy(void) {                 \
    char *p = filetoken##_##exttoken##_copyright;                  \
              filetoken##_##exttoken##_copyright = p;              \
              filetoken##_##exttoken##_dummy(); }

/*!
 * @brief Static copyright string for @e this source file.
 *
 */
ARCH_COPYRIGHT_APACHE(arch, h, "$URL$ $Id$");

#include "config.h"

/*!
 * Definition of platform architectures,
 * including machine hardware type and
 * operating system type.
 *
 * These symbols control various compilation
 * constructs such as integer word width and
 * endianness.
 *
 * One of these deals with real machine architecture,
 * the other with operating system.  It is up to YOU
 * to make sure that both are valid and work together.
 * For example, CONFIG_SPARC32 works with CONFIG_SOLARIS32
 * and CONFIG_LINUX32, but not with CONFIG_WINDOWS64.
 *
 * One of these MUST be defined on the compile
 * line:
 *
 * CONFIG_SPARC32     Sun Sparc architecture, 32-bit word
 * CONFIG_SPARC64     Sun Sparc architecture, 64-bit word
 *
 * CONFIG_INTEL32     Intel x86 architecture, 32-bit word
 * CONFIG_INTEL64     Intel x86 architecture, 64-bit word
 *
 *
 * ... others as available ...
 *
 *
 * One of these MUST be defined on the compile
 * line:
 *
 * CONFIG_SOLARIS32   Sun Solaris, 32-bit word
 * CONFIG_SOLARIS64   Sun Solaris, 64-bit word
 *
 * CONFIG_LINUX32     Linux operating system, 32-bit word
 * CONFIG_LINUX64     Linux operating system, 64-bit word
 *
 * CONFIG_WINDOWS32   Microsoft Windows operating system, 32-bit word
 * CONFIG_WINDOWS64   Microsoft Windows operating system, 64-bit word
 *
 *
 * ... others as available ...
 *
 *
 */

/*!
 * @internal Demand that EXACTLY ONE hardware architecture be defined
 */

#ifdef CONFIG_SPARC32
#define _ARCH_DEFINED_
#endif

#ifdef CONFIG_SPARC64
#ifdef _ARCH_DEFINED_
#error "Multiple machine architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

#ifdef CONFIG_INTEL32
#ifdef _ARCH_DEFINED_
#error "Multiple machine architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

#ifdef CONFIG_INTEL64
#ifdef _ARCH_DEFINED_
#error "Multiple machine architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

/*!
 * @internal Check that that EXACTLY ONE architecture has been defined
 */
#ifndef _ARCH_DEFINED_
#error "Need to explicitly define a machine architecture"
#endif


/* Demand that EXACTLY ONE software architecture be defined */
#undef _ARCH_DEFINED_

#ifdef CONFIG_SOLARIS32
#define _ARCH_DEFINED_
#endif

#ifdef CONFIG_SOLARIS64
#ifdef _ARCH_DEFINED_
#error "Multiple OS architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

#ifdef CONFIG_LINUX32
#ifdef _ARCH_DEFINED_
#error "Multiple OS architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

#ifdef CONFIG_LINUX64
#ifdef _ARCH_DEFINED_
#error "Multiple OS architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

#ifdef CONFIG_WINDOWS32
#ifdef _ARCH_DEFINED_
#error "Multiple OS architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

#ifdef CONFIG_WINDOWS64
#ifdef _ARCH_DEFINED_
#error "Multiple OS architectures defined"
#else
#define _ARCH_DEFINED_
#endif
#endif

/*!
 * @internal Check that that EXACTLY ONE architecture has been defined
 */
#ifdef _ARCH_DEFINED_
/*!
 * @internal Make available, especially to
 * @link jvm/src/jvmcfg.h jvmcfg.h@endlink
 *
 */
#define _VALID_ARCH_DEFINED_
#else
#error "Need to explicitly define an OS architecture"
#endif
#undef _ARCH_DEFINED_

/*!
 * @def ARCH_ODD4_ADDRESS_SIGSEGV
 * @brief Check architectural hardware error oddities related to
 * even/odd byte addressing.
 *
 * The behavioral oddities to be flagged for a specific architecture
 * include:
 *
 * <ul>
 * <li>
 * @b ARCH_ODD2_ADDRESS_SIGSEGV ... When a 2-byte access causes
 *                                  @b SIGSEGV on a read or write
 *                                  operation.
 * </li>
 *
 * <li>
 * @b ARCH_ODD4_ADDRESS_SIGSEGV ... When a 4-byte access causes
 *                                  SIGSEGV on a read or write
 *                                  operation.  This will also mean
 *                                  that a 2-byte access will also
 *                                  cause @b SIGSEGV.
 * </li>
 *
 * <li>
 * @b xyz                       ... Your favorite bug is defined here...
 * </li>
 * </ul>
 *
 */

#ifdef CONFIG_SOLARIS32
#define ARCH_ODD4_ADDRESS_SIGSEGV
#endif

/*!
 * @def ARCH_ODD2_ADDRESS_SIGSEGV
 * @brief See @link
 * #ARCH_ODD4_ADDRESS_SIGSEGV ARCH_ODD4_ADDRESS_SIGSEGV@endlink.
 */
/* rm this if/endif when there is an architecture that needs only ODD2*/
#if 0
#ifdef CONFIG_SOLARIS32
#define ARCH_ODD2_ADDRESS_SIGSEGV
#endif
#endif

/*
 * ... Define other issues here ...
 */



/*********** End of unique definitions.  Start derived definitions ****/


/* Endianness of real machine word */

#ifdef CONFIG_INTEL
/*!
 * @def ARCH_LITTLE_ENDIAN
 * @brief Defined only for little endian architectures, in opposition
 * to @link #ARCH_BIG_ENDIAN ARCH_BIG_ENDIAN@endlink.
 *
 * Used by swapping functions in
 * @link jvm/src/bytegames.c bytegames.c@endlink and
 * derived macros in @link jvm/src/cfmacros.h cfmacros.h@endlink.
 */
#define ARCH_LITTLE_ENDIAN
#else
/*!
 * @def ARCH_BIG_ENDIAN
 * @brief Defined only for big endian architectures, in opposition
 * to @link #ARCH_LITTLE_ENDIAN ARCH_LITTLE_ENDIAN@endlink.
 *
 * Used by swapping functions in
 * @link jvm/src/bytegames.c bytegames.c@endlink and
 * derived macros in @link jvm/src/cfmacros.h cfmacros.h@endlink.
 */
#define ARCH_BIG_ENDIAN
#endif

/*!
 * @brief Define more general case of odd-address @b SIGSEGV.
 *
 * If either ARCH_ODD4_ADDRESS_SIGSEGV or ARCH_ODD2_ADDRESS_SIGSEGV
 * are defined, then this symbol is also defined as a union of the
 * definitions.
 */
#ifdef  ARCH_ODD4_ADDRESS_SIGSEGV
#define ARCH_ODD_ADDRESS_SIGSEGV
#else
#ifdef  ARCH_ODD2_ADDRESS_SIGSEGV
#define ARCH_ODD_ADDRESS_SIGSEGV
#endif
#endif

#endif /* _arch_h_included_ */

/* EOF */
