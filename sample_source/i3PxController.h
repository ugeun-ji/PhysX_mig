#pragma once

#include "i3PxSimulation.h"

namespace i3Px
{
	struct I3_EXPORT_PX ControllerDesc
	{
		i3::string	name;
		UINT32		id;
		VEC3D		position;
		VEC3D		upDirection;
		REAL32		slopeLimit;
		REAL32		invisibleWallHeight;
		REAL32		maxJumpHeight;
		REAL32		contactOffset;
		REAL32		stepOffset;
		REAL32		density;
		REAL32		scaleCoeff;
		REAL32		volumeGrowth;
		Material*	material;

		UserControllerHitReportPtr		hitReport;			// PhysX user hit callback.
		CCTFilterCallbackPtr			CCTFilterCallback;	// user filtering callback for controller-controller.
		ControllerBehaviorCallbackPtr	behaviorCallback;	// customize the character's behavior after touching a PxShape, a PxController, or a PxObstacle.
	};

	I3_EXPORT_PX void InitializeControllerDesc(ControllerDesc& src);

	struct CCTCollisionFlag
	{
		enum Type
		{
			Side	= (1<<0),
			Up		= (1<<1),
			Down	= (1<<2),
		};
	};

	typedef Flags<CCTCollisionFlag::Type, UINT8> CCTCollisionFlags;

	I3_EXPORT_PX void ToCCTCollisionFlags(const PxControllerCollisionFlags& src, CCTCollisionFlags& out);

	struct CCTNonWalkableMode
	{
		enum Type
		{
			None,
			PreventClimbing,
			ForceSliding,
		};
	};

	I3_EXPORT_PX CCTNonWalkableMode::Type ToCCTNonWalkableMode(PxControllerNonWalkableMode::Enum src);
	I3_EXPORT_PX PxControllerNonWalkableMode::Enum ToPxCCTNonWalkableMode(CCTNonWalkableMode::Type src);

	class Scene;
	class DynamicActor;

	class I3_EXPORT_PX Controller
	{
	public:
		Controller();
		explicit Controller(Scene* scene);
		Controller(const ControllerDesc& desc, Scene* scene);
		virtual ~Controller();

		virtual Enums::Controller::Type		GetType() const = 0;

		virtual PxController*				GetPxController() const;

		virtual void						SetName(const char* name);
		virtual const char*					GetName() const;

		virtual DynamicActor*				GetDynamicActor() const;

		virtual void						Move(const VEC3D& displacement, REAL32 minDist, const FilterData& fd, CCTCollisionFlags& outCollisions);

		virtual void						SetHitCallback(ControllerHitCallbackPtr callback);
		virtual ControllerHitCallbackPtr	GetHitCallback() const;

		virtual void						SetCCTFilterCallback(CCTFilterCallbackPtr callback);
		virtual CCTFilterCallbackPtr		GetCCTFilterCallback() const;

		virtual void						SetQueryFilterCallback(QueryFilterCallbackPtr callback);
		virtual QueryFilterCallbackPtr		GetQueryFilterCallback() const;

		virtual void						SetPosition(const VEC3D& v);
		virtual VEC3D						GetPosition() const;

		virtual void						SetUpDirection(const VEC3D& v);
		virtual VEC3D						GetUpDirection() const;

		virtual void						SetSlopeLimit(REAL32 limit);
		virtual REAL32						GetSlopeLimit() const;

		virtual void						SetContactOffset(REAL32 offset);
		virtual REAL32						GetContactOffset() const;

		virtual void						SetStepOffset(REAL32 offset);
		virtual REAL32						GetStepOffset() const;

		virtual void						SetNonWalkableMode(CCTNonWalkableMode::Type mode);
		virtual CCTNonWalkableMode::Type	GetNonWalkableMode() const; 
		
		void* userData;

	protected:
		i3::string		m_name;

		Scene*			m_scene;
		PxController*	m_controllerPx;
		DynamicActor*	m_dynamicActor;

		ControllerHitCallbackPtr		m_hitCallback;
		CCTFilterCallbackPtr			m_CCTFilterCallback;
		QueryFilterCallbackPtr			m_queryFilterCallback;
		ControllerBehaviorCallbackPtr	m_behaviorCallback;

		i3Timer m_timer;
	};

	namespace ControllerExt
	{
		I3_EXPORT_PX void EnableSimulation(Controller& controller, bool ok);
		I3_EXPORT_PX bool IsSimulationEnable(Controller& controller);
		
		I3_EXPORT_PX void EnableSceneQuery(Controller& controller, bool ok);

		namespace Nx
		{
			I3_EXPORT_PX void	SetCollisionGroup(Controller& controller, UINT32 group);
			I3_EXPORT_PX UINT32 GetCollisionGroup(const Controller& controller);
			I3_EXPORT_PX void	Move(Controller& controller, const VEC3D& displacement, REAL32 minDist, INT32 groupMask, CCTCollisionFlags& outCollisions);

			I3_EXPORT_PX CCTCollisionFlags ToCCTCollisionFlags(UINT32 flagsNx);
		}
	}
}