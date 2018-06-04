#pragma once

#include "i3PxRigidBody.h"

namespace i3Px
{
	struct I3_EXPORT_PX DynamicActorDesc
	{
		RigidBodyDesc rigidBody;

		REAL32 linearDamping;
		REAL32 angularDamping;
		REAL32 maxAngularVelocity;
		REAL32 density;
		UINT32 solverIterationCount;
		REAL32 sleepThreshold;
		REAL32 contactReportThreshold;
		bool isKinematicMode;
	};

	I3_EXPORT_PX void InitializeDynamicActorDesc(DynamicActorDesc& desc);

	class I3_EXPORT_PX DynamicActor : public RigidBody
	{
	public:
		DynamicActor();
		DynamicActor(const DynamicActorDesc& actorDesc, Scene* scene);
		virtual ~DynamicActor();

		virtual void				SetLinearDamping(REAL32 damp);
		virtual REAL32				GetLinearDamping() const;

		virtual void				SetAngularDamping(REAL32 damp);
		virtual REAL32				GetAngularDamping() const;

		virtual void				SetMaxAngularVelocity(REAL32 maxAngVel);
		virtual REAL32				GetMaxAngularVelocity() const;

		virtual void				SetDensity(REAL32 density);
		virtual REAL32				GetDensity() const;

		virtual void				Sleep();
		virtual void				WakeUp();
		virtual bool				IsSleeping() const;

		virtual void				SetSleepThreshold(REAL32 threshold);
		virtual REAL32				GetSleepThreshold() const;

		virtual void				SetStabilizationThreshold(REAL32 threshold);
		virtual REAL32				GetStabilizationThreshold() const;

		virtual void				SetContactReportThreshold(REAL32 threshold);
		virtual REAL32				GetContactReportThreshold() const;

		virtual void				SetSolverIterationCount(UINT32 count);
		virtual UINT32				GetSolverIterationCount() const;

		virtual void				EnableKinematicMode(bool ok);
		virtual bool				IsKinematicMode() const;
		virtual void				SetKinematicTarget(const MATRIX& destination);

		virtual Enums::Actor::Type	GetType() const;
		virtual bool				IsKindOf(const char* name) const;

	private:
		REAL32 m_density;
	};

	namespace DynamicActorExt
	{
		I3_EXPORT_PX void RetrieveDynamicActorDesc(const DynamicActor& actor, DynamicActorDesc& out);
	}
}