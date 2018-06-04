#pragma once

//#include "i3PxPCH.h"
#include "i3PxSimulation.h"
#include "i3PxSceneQuery.h"
#include "i3PxFilterData.h"

namespace i3Px
{
	class I3_EXPORT_PX GeometryDesc
	{
	public:
		GeometryDesc();

		virtual Enums::Geometry::Type	GetType() const			= 0;
		virtual PxGeometryPtr			ToPxGeometry() const	= 0;

	public:
		i3::string	name;
		MATRIX		localPose;
		REAL32		contactOffset;
		REAL32		restOffset;
		FilterData	simulationFilterData;
		FilterData	sceneQueryFilterData;
		bool		isSimulationEnable;
		bool		isSceneQueryEnable;
		bool		isTrigger;
		void*		userData;
	};

	I3_EXPORT_PX void ShapeToGeometryDesc(Shape* shape, GeometryDesc& out);

	class I3_EXPORT_PX Shape
	{
	public:
		Shape();
		explicit Shape(Scene* scene);
		virtual ~Shape() = 0;

		bool								Create(const GeometryDesc& desc, bool isExclusive);

		virtual void						SetLocalPose(const MATRIX& mat);
		virtual MATRIX						GetLocalPose() const;

		virtual void						SetSimulationFilterData(const FilterData& fd);
		virtual FilterData					GetSimulationFilterData() const;

		virtual void						SetSceneQueryFilterData(const FilterData& fd);
		virtual FilterData					GetSceneQueryFilterData() const;

		virtual void						ResetFilterData();

		virtual void						SetContactOffset(REAL32 contactOffset);
		virtual REAL32						GetContactOffset() const;

		virtual void						SetRestOffset(REAL32 restOffset);
		virtual REAL32						GetRestOffset() const;

		virtual void						EnableSimulation(bool ok);
		virtual bool						IsSimulationEnable() const;

		virtual void						EnableSceneQuery(bool ok);
		virtual bool						IsSceneQueryEnable() const;

		virtual void						EnableTrigger(bool ok);
		virtual bool						IsTrigger() const;

		virtual void						SetName(const char* name);
		virtual const char*					GetName() const;

		virtual bool						IsExclusive() const;

		virtual RigidActor*					GetActor() const;
		
		virtual void						SetPxShape(PxShape* shapePx);
		virtual PxShape*					GetPxShape() const;

		virtual void						DetachPxShape();
		virtual void						ReleasePxShape();

		virtual Enums::Geometry::Type		GetGeometryType() const = 0;
		
		virtual GeometryDescPtr				RetrieveGeometryDesc() = 0;

		void* userData;	// for user.

	protected:
		virtual PxShape*	_CreatePxShape(const GeometryDesc& desc, bool isExclusive) = 0;

		Scene*					m_scene;
		PxShape*				m_shapePx;
		i3::vector<RigidActor*> m_actors;
	};

	class I3_EXPORT_PX SingleMaterialable
	{
	public:
		SingleMaterialable();
		virtual ~SingleMaterialable() = 0;

		virtual void		SetMaterial(Material& material, Shape& shape);
		virtual Material*	GetMaterial() const;

	protected:
		Material* m_material;
	};

	class I3_EXPORT_PX MultipleMaterialable
	{
	public:
		MultipleMaterialable();
		virtual ~MultipleMaterialable() = 0;

		virtual void							SetMaterials(const i3::vector<Material*>& materials, Shape& shape);
		virtual i3::vector<Material*>&			GetMaterials();
		virtual const i3::vector<Material*>&	GetMaterials() const;

	protected:
		i3::vector<Material*> m_materials;
	};

	namespace ShapeExt
	{
		I3_EXPORT_PX PxGeometryType::Enum	ToPxGeometryType(Enums::Geometry::Type type);
		I3_EXPORT_PX Enums::Geometry::Type	ToGeometryType(PxGeometryType::Enum type);

		I3_EXPORT_PX void					SetMaterials(const i3::vector<Material*>& materials, Shape& shape);
		I3_EXPORT_PX void					GetMaterials(const Shape& shape, i3::vector<Material*>& out);

		I3_EXPORT_PX void					CalcShapeWorldPose(const Shape& shape, MATRIX& actorWorldPose, MATRIX& out);
		I3_EXPORT_PX void					GetShapeWorldPose(const Shape& shape, MATRIX& out);

		I3_EXPORT_PX PxBounds3				GetWorldAABB(const Shape& shape);

		namespace Nx
		{
			I3_EXPORT_PX void				SetGroup(Shape& shape, UINT32 group);
			I3_EXPORT_PX UINT32				GetGroup(const Shape& shape);

			I3_EXPORT_PX void				SetGroupsMask(Shape& shape, const Simulation::Nx::FilteringGroups& filtering);
		}
	}
}