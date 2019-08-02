# postgresql 基于 C 语言的拓展

* 新建文件夹
    * mkdir new_town_method

* 创建四个文件 Makefile, new_town_method.c, new_town_method.control, new_town_method--0.0.1.sql

    * Makefile

            MODULES = new_town_method		    # 扩展的名称
            EXTENSION =	new_town_method
            DATA = new_town_method--0.0.1.sql   # 扩展安装的SQL文件

            <!-- REGRESS = new_town_method_test      # 扩展测试的SQL文件 -->
            # PostgreSQL 构建扩展相关的命令，固定格式
            PG_CONFIG = pg_config
            PGXS := $(shell $(PG_CONFIG) --pgxs)
            include $(PGXS)

    * new_town_method.control 控制文件，声明该扩展的基础信息

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

            #include "postgres.h"   //包含 PostgreSQL 基础的接口
            #include "fmgr.h"       //包含了PG_GETARG_XX和PG_RETURN_XX等获取参数和返回结果的重要的宏
            #include <math.h>

            PG_MODULE_MAGIC;        //PG_MODULE_MAGIC 是一个从 PostgreSQL 8.2版本后就必须的宏，必须写在#include "fmgr.h"之后

            // PG_FUNCTION_INFO_V1 宏声明了我们所定义的函数为 Version-1 约定的函数。我们选择了 Version-1 的开发约定，所以在定义方法之前，需要调用
            PG_FUNCTION_INFO_V1(new_town_method);

            float8 new_town_method_power(float8 xn_value, int32 value_to_power, int32 loop_time, int32 pow_value);

            // Datum 等同于void *，表示函数返回任意类型的数据
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

* 测试 TEST
    * 新建 sql 文件夹，创建 new_town_method_test.sql

            CREATE EXTENSION new_town_method;

            select new_town_method(1, 2, 3, 4);
            select new_town_method(1, 5, 3, 4);
    * 在 Makefile 文件里面添加

            REGRESS = new_town_method_test
    * 新建 expected 文件夹
    * 执行 make && make installcheck ， 会在 results 文件夹里面输出结果，将该输出，复制到 expected里面，文件 new_town_method_test.out

            CREATE EXTENSION new_town_method;
            select new_town_method(1, 2, 3, 4);
            new_town_method  
            ------------------
            1.41421568627451
            (1 row)

            select new_town_method(1, 5, 3, 4);
            new_town_method  
            ------------------
            2.23809523809524
            (1 row)

    * make clean && make && make installcheck