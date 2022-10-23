/*
 * BIT_MATH.h
 *
 * Created: 03/04/2022 10:12:25 ص
 *  Author: HOSSAM MOSTAFA
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)			REG |= (1 << BIT)
#define CLR_BIT(REG,BIT)			REG &= ~(1 << BIT)
#define TOG_BIT(REG,BIT)			REG ^= (1 << BIT)
#define GET_BIT(REG,BIT)			1 & (REG >> BIT)
#define MASK_BIT(REG,BIT,DATA)      REG |= (DATA << BIT)

#define SET_REG(REG)				REG |= 0xFF  
#define CLR_REG(REG)				REG &= 0
#define TOG_REG(REG)				REG ^= 0xFF
#define GET_REG(REG)				0xFF & (REG)
#define MASK_REG(REG,DATA)			REG |= (DATA)

#endif /* BIT_MATH_H_ */