#pragma once
#include "spatial/common.hpp"
#include "spatial/core/geometry/vertex_vector.hpp"
#include "spatial/core/geometry/geometry.hpp"
#include "spatial/core/geometry/geometry_factory.hpp"

namespace spatial {

namespace core {

class WKBReader {
private:
	ArenaAllocator &arena;
	bool has_any_z;
	bool has_any_m;

	struct WKBType {
		GeometryType type;
		bool has_z;
		bool has_m;
	};

	// Primitives
	uint32_t ReadInt(Cursor &cursor, bool little_endian);
	double ReadDouble(Cursor &cursor, bool little_endian);
	WKBType ReadType(Cursor &cursor, bool little_endian);

	// Geometries
	Point ReadPoint(Cursor &cursor, bool little_endian, bool has_z, bool has_m);
	LineString ReadLineString(Cursor &cursor, bool little_endian, bool has_z, bool has_m);
	Polygon ReadPolygon(Cursor &cursor, bool little_endian, bool has_z, bool has_m);
	MultiPoint ReadMultiPoint(Cursor &cursor, bool little_endian);
	MultiLineString ReadMultiLineString(Cursor &cursor, bool little_endian);
	MultiPolygon ReadMultiPolygon(Cursor &cursor, bool little_endian);
	GeometryCollection ReadGeometryCollection(Cursor &cursor, bool little_endian);
	Geometry ReadGeometry(Cursor &cursor);

public:
	explicit WKBReader(ArenaAllocator &arena) : arena(arena) {
	}
	Geometry Deserialize(const string_t &wkb);
	Geometry Deserialize(const_data_ptr_t wkb, uint32_t size);
	bool GeomHasZ() const {
		return has_any_z;
	}
	bool GeomHasM() const {
		return has_any_m;
	};
};

} // namespace core

} // namespace spatial
