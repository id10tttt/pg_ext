-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION new_town_method" to load this file. \quit
CREATE OR REPLACE FUNCTION
new_town_method(float, int, int, int) RETURNS float AS 'MODULE_PATHNAME','new_town_method'
LANGUAGE C IMMUTABLE CALLED ON NULL INPUT;