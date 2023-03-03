CREATE EXTENSION postgis;
-- in PostGIS 3, postgis_raster is a separate extension from postgis
-- so do this in addition if you are experimenting PostGIS 3+
CREATE EXTENSION postgis_raster;
CREATE EXTENSION postgis_sfcgal;
CREATE EXTENSION address_standardizer;
CREATE EXTENSION fuzzystrmatch;
CREATE EXTENSION postgis_topology;
CREATE EXTENSION postgis_tiger_geocoder;

ALTER TABLE geo_test.test_point
ADD COLUMN geom geometry(POINTZ);

UPDATE geo_test.test_point set geom = ST_GeomFromText('POINTZ(1 0 0)') WHERE id = 1;
UPDATE geo_test.test_point set geom = ST_GeomFromText('POINTZ(0 1 0)') WHERE id = 2;
UPDATE geo_test.test_point set geom = ST_GeomFromText('POINTZ(0 0 1)') WHERE id = 3;

select ST_AsGeoJSON(t.*) geom from geo_test.test_point as t(geom);
