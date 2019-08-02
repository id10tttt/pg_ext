#include "postgres.h"
#include "fmgr.h"
#include <math.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(new_town_method);

float8 new_town_method_power(float8 xn_value, int32 value_to_power, int32 loop_time, int32 pow_value);

Datum
new_town_method(PG_FUNCTION_ARGS){
    float8 xn_value = PG_GETARG_FLOAT8(0);
    int32 value_to_power = PG_GETARG_INT32(1);
    int32 loop_time = PG_GETARG_INT32(2);
    int32 pow_value = PG_GETARG_INT32(3);

    float8 res;
    res = new_town_method_power(xn_value, value_to_power, loop_time, pow_value);

    PG_RETURN_FLOAT8(res);
}

float8 new_town_method_power(float8 xn_value, int32 value_to_power, int32 loop_time, int32 pow_value){
    float8 tmp;
    int32 i;

    for(i = 0; i < loop_time; i ++){
        tmp = xn_value;
        xn_value = tmp - (pow(tmp, pow_value) - value_to_power) / (pow_value * pow(tmp, pow_value - 1));
    }
    return xn_value;
}