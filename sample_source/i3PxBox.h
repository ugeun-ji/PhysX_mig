#pragma once

#include "i3PxShape.h"

namespace i3Px
{
	class I3_EXPORT_PX BoxGeometryDesc : public GeometryDesc
	{
	public:
		BoxGeometryDesc();
		virtual ~BoxGeometryDesc();

		virtual Enums::Geometry::Type	GetType() const;
		virtual PxGeometryPtr			ToPxGeometry() const;

	public:
		VEC3D		halfExtents;
		Material*	material;
	};

	class I3_EXPORT_PX Box : public Shape, public SingleMaterialable
	{
	public:
		Box();
		explicit Box(Scene* scene);
		virtual ~Box();

		static ShapePtr					Creator(Scene* scene);

		virtual Enums::Geometry::Type	GetGeometryType() const;
		virtual GeometryDescPtr			RetrieveGeometryDesc();

		virtual void					SetHalfExtents(const VEC3D& v);
		virtual VEC3D					GetHalfExtents() const;

	protected:
		virtual PxShape* _CreatePxShape(const GeometryDesc& desc, bool isExclusive);
	};
}
