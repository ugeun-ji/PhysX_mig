#pragma once

namespace i3Px
{
	struct RaycastHit;
	struct OverlapHit;
	struct SweepHit;
	class Controller;
	class Shape;
	class Actor;
	struct ContactPair;
	struct PairFound;
	struct PairLost;
	struct TriggerEvent;

	class I3_EXPORT_PX Callback
	{
	public:
		Callback() {}
		virtual ~Callback() {}

		virtual void			OnContact(const ContactPair& contact)					{}
		virtual void			OnSleep()												{}
		virtual void			OnWake()												{}
		virtual void			OnRaycast(RaycastHit& raycast)							{}
		virtual void			OnOverlap(OverlapHit& overlap)							{}
		virtual void			OnSweep(SweepHit& sweep)								{}
		virtual void			OnTriggerEvent(const TriggerEvent& info)				{}
		virtual void			OnControllerShapeHit(Controller& controller, Shape& shape, const VEC3D& dir, REAL32 length, const VEC3D& worldNormal, const VEC3D& worldPos)						{}
		virtual void			OnControllerShapeHit(Controller& controller, Shape& shape, const VEC3D& dir, REAL32 length, UINT32 triangleIndex, const VEC3D& worldNormal, const VEC3D& worldPos)	{}
		virtual PxFilterFlags	OnPairFound(const PairFound& pair)						{ return PxFilterFlags(); }
		virtual void			OnPairLost(const PairLost& pair)						{}
		virtual bool			OnStatusChange(PxU32 &pairID, PxPairFlags &pairFlags, PxFilterFlags &filterFlags) { return false; }
	};

	class I3_EXPORT_PX CallbackNull : public Callback
	{
	public:
		CallbackNull() {}
		virtual ~CallbackNull() {}
	};
}
