# postgresql 基于 C 语言的拓展

* 新建文件夹
    * mkdir new_town_method

* 创建四个文件 Makefile, new_town_method.c, new_town_method.control, new_town_method--0.0.1.sql

    * Makefile

            MODULES = new_town_method		# 扩展的名称
            EXTENSION =	new_town_method
            DATA = new_town_method--0.0.1.sql

            # 以下是 PostgreSQL 构建扩展相关的命令，保留就可以
            PG_CONFIG = pg_config
            PGXS := $(shell $(PG_CONFIG) --pgxs)
            include $(PGXS)

    * new_town_method.control

            comment = 'Newtown methpod for postgresql function extend by C language'
            default_version = '0.0.1'
            relocatable = true
            module_pathname = '$libdir/new_town_method'
    * new_town_method--0.0.1.sql

            -- complain if script is sourced in psql, rather than via CREATE EXTENSION
            \echo Use "CREATE EXTENSION new_town_method" to load this file. \quit
            CREATE OR REPLACE FUNCTION
            new_town_method(float, int, int, int) RETURNS float AS 'MODULE_PATHNAME','new_town_method'
            LANGUAGE C IMMUTABLE CALLED ON NULL INPUT;
    
    * new_town_method.c

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
                // printf("%f %d %d %d", xn_value, value_to_power, loop_time, pow_value);
                res = new_town_method_power(xn_value, value_to_power, loop_time, pow_value);

                PG_RETURN_FLOAT8(res);
            }

            float8 new_town_method_power(float8 xn_value, int32 value_to_power, int32 loop_time, int32 pow_value){
                float8 tmp;
                int32 i;

                for(i = 0; i < loop_time; i ++){
                    tmp = xn_value;
                    xn_value = 1/2.0 * (tmp + value_to_power / tmp);
                    // xn_value = ((pow_value - 1) / pow_value) * tmp + value_to_power / (pow_value * pow(tmp, pow_value - 1));
                }
                // PG_RETURN_FLOAT8(xn_value);
                return xn_value;
            }
* 编译 make && sudo make install

* test