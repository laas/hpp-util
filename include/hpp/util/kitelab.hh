// Copyright (C) 2013 by Antonio El Khoury, CNRS.
//
// This file is part of the hpp-util.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_UTIL_KITELAB_HH
# define HPP_UTIL_KITELAB_HH

/** Defines the four types of smart pointers associated with type <tt>\a t</tt>.
*   If <tt>\a t</tt> is \c CMyClass then
*   - the type of a shared pointer to <tt>\a t</tt> is \c CMyClassShPtr
*   - the type of a weak pointer to <tt>\a t</tt> is \c CMyClassWkPtr
*   - the type of a shared pointer to <tt>\a t const</tt> is \c CMyClassConstShPtr
*   - the type of a weak pointer to <tt>\a t const</tt> is \c CMyClassConstWkPtr
*/
# define HPP_KIT_POINTER_DEFS(t)		 \
  typedef KIT_SHARED_PTR(t) t##ShPtr;		 \
  typedef KIT_WEAK_PTR(t) t##WkPtr;		 \
  typedef KIT_SHARED_PTR_CONST(t) t##ConstShPtr; \
  typedef KIT_WEAK_PTR_CONST(t) t##ConstWkPtr

/** Makes a forward declaration of class <tt>\a t</tt> and of the four
*   types of shared pointers associated with it.
*/
# define HPP_KIT_PREDEF_CLASS(t)		\
  class t;					\
  HPP_KIT_POINTER_DEFS(t)

/** Macro used to add a CkcdDetector to the default detector list
 *		\param detectorClass Name of a subclass of CkcdDetector.
 *			This class must define a create() static method that
 *			returns a shared pointer to the newly created detector.
 *		\note do not use this macro in the detector's cpp if no reference
 *			to the detector is made outside the class : if linking the library
 *			as a static library, the class may be removed entirely by the linker !
 */
#define HPP_KCD_REGISTER_DETECTOR(detectorClass)	\
  size_t detectorClass##DummyFunctionReturn =		\
    CkcdGlobal::instance().registerDetector		\
    (&CkcdGlobal::createDetector<detectorClass>)

/** Macro used to add a CkcdTestTreeLocked to the default tree list
*		\param treeClass Name of a subclass of CkcdTestTreeLocked.
*			This class must define a create(const CkcdObjectShPtr&) static method 
*			that takes the collision entity as a parameter
*			and returns a shared pointer to the newly created tree.
*		\note do not use this macro in the tree's cpp if no reference
*			to the tree is made outside the class : if linking the library
*			as a static library, the class may be removed entirely by the linker !
*/
#define HPP_KCD_REGISTER_TEST_TREE_LOCKED(treeClass)	\
  size_t treeClass##DummyFunctionReturn =		\
    CkcdGlobal::instance().registerTestTreeLocked	\
    (&CkcdGlobal::createTestTreeLocked<treeClass>)

#define HPP_KPP_DECLARE_PROPERTY( P )		       \
  static const CkppProperty::TPropertyID P##_PROPERTY; \
  static const std::string P##_PROPERTY_STRING_ID

#endif //! HPP_UTIL_KITELAB_HH
