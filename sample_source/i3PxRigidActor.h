#pragma once

#include "i3PxActor.h"
#include "i3PxShape.h"

namespace i3Px
{
	struct I3_EXPORT_PX RigidActorDesc
	{
		ActorDesc base;

		MATRIX	globalPose;
		i3::vector<Shape*> shapes;
	};

	I3_EXPORT_PX void InitializeRigidActorDesc(RigidActorDesc& desc);

	// shapes and transforms.
	class RigidActor : public Actor
	{
	public:
		RigidActor();
		explicit RigidActor(Scene* scene);
		virtual ~RigidActor() = 0;

		virtual void						SetGlobalPose(const MATRIX& mtx);
		virtual MATRIX						GetGlobalPose() const;

		virtual void						AttachShape(Shape& shape);
		virtual void						DetachShape(Shape& shape);

		virtual i3::vector<Shape*>&			GetShapes();
		virtual const i3::vector<Shape*>&	GetShapes() const;

		virtual void						SetPxActor(PxActor* actor, Scene* scene);
		virtual void						DetachPxActor();

		virtual bool						IsKindOf(const char* name) const;

	protected:
		void _Initialize(const RigidActorDesc& desc, Scene* scene);
		void _AttachShape(Shape& shape);
		void _DetachShape(Shape& shape);

		i3::vector<Shape*> m_shapes;	// actor 가 static 이건 dynamic 이건 컬리전을 위한 shape 를 반드시 하나 이상 가져야 한다.
	};

	namespace RigidActorExt
	{
		I3_EXPORT_PX void RetrieveRigidActorDesc(const RigidActor& actor, RigidActorDesc& out);

		I3_EXPORT_PX void EnableSimulation(RigidActor& actor, bool ok);
		I3_EXPORT_PX void EnableSceneQuery(RigidActor& actor, bool ok);
		I3_EXPORT_PX void EnableTrigger(RigidActor& actor, bool ok);

		namespace Nx
		{
			// for NX_AF_DISABLE_COLLISION flag.
			I3_EXPORT_PX void	EnableCollision(RigidActor& actor, bool ok);

			// for setGroup / getGroup of NxActor.
			I3_EXPORT_PX void	SetGroup(RigidActor& actor, UINT32 group);
			I3_EXPORT_PX UINT32	GetGroup(const RigidActor& actor);

			// for setGroupsMask of NxShape.
			I3_EXPORT_PX void	SetGroupsMask(RigidActor& actor, const Simulation::Nx::FilteringGroups& filtering);
		}
	}
}
