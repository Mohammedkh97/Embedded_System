/*
 * Utils.h
 *
 * Created: 10/10/2023 4:36:43 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define   GET_BIT(value, bit)      ((value >> bit) &1)
#define   SET_BIT(value, bit)      (value = value|(1 << bit))
#define   CLEAR_BIT(value, bit)    (value = value & ~(1 << bit))
#define   TOGGLE_BIT(value, bit)   (value = value^(1 << bit))


#endif /* UTILS_H_ */