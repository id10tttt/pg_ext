# 扩展的名称
MODULES = new_town_method
EXTENSION =	new_town_method
DATA = new_town_method--0.0.1.sql

# 测试
REGRESS = new_town_method_test

# 以下是 PostgreSQL 构建扩展相关的命令，保留就可以
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)