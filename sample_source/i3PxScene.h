#pragma once

#include <unordered_map>
#include <map>
#include "i3PxSimulationScale.h"
#include "i3PxBoxController.h"
#include "i3PxCapsuleController.h"
#include "i3PxTriggerCallback.h"

namespace i3Px
{
	namespace SceneQuery { struct Groups; }

	struct I3_EXPORT_PX SceneDesc
	{
		i3::string					name;
		SimulationScale				scale;
		VEC3D						gravity;
		const void*					filterShaderData;
		UINT32						filterShaderDataSize;
		PxSimulationFilterShader	filterShader;
		PxBroadPhaseType::Enum		broadPhaseType;
		PxSceneLimits				limits;
		REAL32						meshContactMargin;
		PxFrictionType::Enum		frictionType;
		REAL32						contactCorrelationDistance;
		REAL32						bounceThresholdVelocity;
		REAL32						frictionOffsetThreshold;
		PxSceneFlags				flags;
		PxCpuDispatcher*			cpuDispatcher;
		PxGpuDispatcher* 			gpuDispatcher;
		PxSpuDispatcher*			spuDispatcher;
		PxPruningStructure::Enum	staticStructure;
		PxPruningStructure::Enum	dynamicStructure;
		UINT32						dynamicTreeRebuildRateHint;
		void*						userData;
		UINT32						solverBatchSize;
		UINT32						nbContactDataBlocks;
		UINT32						maxNbContactDataBlocks;
		UINT32						contactReportStreamBufferSize;
		UINT32						ccdMaxPasses;
		PxSimulationOrder::Enum		simulationOrder;
		REAL32						wakeCounterResetValue;
		PxBounds3					sanityBounds;
	};

	I3_EXPORT_PX void InitializeSceneDesc(const SimulationScale& scale, SceneDesc& desc);
	I3_EXPORT_PX void ToPxScene(const SceneDesc& desc, PxSceneDesc& out);

	class I3_EXPORT_PX Scene
	{
	public:
		typedef i3::vector<ActorPtr>										Actors;
		typedef i3::vector<ShapePtr>										Shapes;
		typedef i3::vector<MaterialPtr>										Materials;
		typedef i3::vector<JointPtr>										Joints;
		typedef i3::vector<ControllerPtr>									Controllers;
		typedef i3::vector<TriggerEvent>									TriggerEvents;
		typedef i3::map<Enums::Priority::Type, TimeListenerGroupPtr>		TimeListenerGroups;

		Scene(const SceneDesc& sceneDesc, PxPhysics* sdk);
		~Scene();

		// contact callback.
		void					SetContactCallback(CallbackPtr callback);
		CallbackPtr				GetContactCallback() const;

		// actors.
		DynamicActor&			CreateDynamicActor(const DynamicActorDesc& actorDesc);
		StaticActor&			CreateStaticActor(const StaticActorDesc& actorDesc);
		PlaneActor&				CreatePlaneActor(const PlaneActorDesc& desc);
		void					AddActor(const ActorPtr& actor);
		void					DestroyActor(const Actor& actor);
		void					ClearActors();
		
		// material.
		Material&				CreateMaterial(const MaterialDesc& desc);
		void					DestroyMaterial(const Material& mtl);
		Material&				GetMaterial(size_t idx) const;
		bool					FindMaterial(const char* name, i3::vector<Material*>& out) const;
		Material&				FindMaterial(REAL32 dynamicFriction, REAL32 staticFriction, REAL32 restitution) const;
		void					GetMaterials(i3::vector<Material*>& out) const;
		Material&				GetDefaultMaterial() const;
		void					ClearMaterials();

		// shapes.
		Shape&					CreateShape(const GeometryDesc& desc, bool isExclusive);
		void					DestroyShape(Shape& shape);
		void					AddShape(ShapePtr& shape);
		bool					FindShape(const char* name, i3::vector<Shape*>& out) const;
		void					GetShapes(i3::vector<Shape*>& out) const;
		void					ClearShapes();

		// joints.
		FixedJoint&				CreateFixedJoint(const FixedJointDesc& desc);
		RevoluteJoint&			CreateRevoluteJoint(const RevoluteJointDesc& desc);
		SphericalJoint&			CreateSphericalJoint(const SphericalJointDesc& desc);
		DistanceJoint&			CreateDistanceJoint(const DistanceJointDesc& desc);
		PrismaticJoint&			CreatePrismaticJoint(const PrismaticJointDesc& desc);
		D6Joint&				CreateD6Joint(const D6JointDesc& desc);
		void					DestroyJoint(const Joint& joint);
		void					GetJoints(i3::vector<Joint*>& out) const;
		void					ClearJoints();

		// raycast.
		bool					CheckRaycastAny(const Ray& ray, REAL32 distance) const;
		bool					RaycastSingle(const Ray& ray, REAL32 distance, const FilterData& fd, RaycastHit& out, PxQueryFlags query = PxQueryFlag::eDYNAMIC|PxQueryFlag::eSTATIC) const;
		bool					RaycastMultiple(const Ray& ray, REAL32 distance, const FilterData& fd, i3::vector<RaycastHitPtr>& outList, UINT32 bufferSize = 256, PxQueryFlags query = PxQueryFlag::eDYNAMIC|PxQueryFlag::eSTATIC) const;

		// overlap.
		bool					CheckOverlapAny(const GeometryDesc& shape, const MATRIX& pose) const;
		bool					OverlapSingle(const GeometryDesc& shape, const MATRIX& pose, const FilterData& fd, OverlapHit& out, PxQueryFlags query = PxQueryFlag::eDYNAMIC|PxQueryFlag::eSTATIC) const;
		bool					OverlapMultiple(const GeometryDesc& shape, const MATRIX& pose, const FilterData& fd, i3::vector<OverlapHitPtr>& outList, UINT32 bufferSize = 256, PxQueryFlags query = PxQueryFlag::eDYNAMIC|PxQueryFlag::eSTATIC) const;

		// sweep.
		bool					CheckSweepAny(const GeometryDesc& shape, const MATRIX& pose, const VEC3D& dir, REAL32 distance) const;
		bool					SweepSingle(const GeometryDesc& shape, const MATRIX& pose, const VEC3D& dir, REAL32 distance, const FilterData& fd, SweepHit& out, PxQueryFlags query = PxQueryFlag::eDYNAMIC|PxQueryFlag::eSTATIC) const;
		bool					SweepMultiple(const GeometryDesc& shape, const MATRIX& pose, const VEC3D& dir, REAL32 distance, const FilterData& fd, i3::vector<SweepHitPtr>& outList, UINT32 bufferSize = 256, PxQueryFlags query = PxQueryFlag::eDYNAMIC|PxQueryFlag::eSTATIC) const;

		// simulate.
		void					Simulate(const REAL32 tm);
		bool					CheckResults(bool block = false);
		
		// frame works.
		void					AddSimulateListener(TimeListenerPtr listener, Enums::Priority::Type prior = Enums::Priority::Medium);
		void					RemoveSimulateListener(TimeListenerPtr listener, Enums::Priority::Type prior);

		void					AddRenderListener(TimeListenerPtr listener, Enums::Priority::Type prior = Enums::Priority::Medium);
		void					RemoveRenderListener(TimeListenerPtr listener, Enums::Priority::Type prior);

		// character controller.
		PxControllerManager*	GetPxControllerManager() const;

		BoxController&			CreateBoxController(const BoxControllerDesc& desc);
		CapsuleController&		CreateCapsuleController(const CapsuleControllerDesc& desc);
		void					DestroyController(const Controller& controller);
		void					ClearControllers();

		// trigger event for PxPairFlag::eNOTIFY_TOUCH_PERSISTS.
		void					OnTriggerEvent(const TriggerEvent& evt);
		void					ClearTriggerEvents();

		// sdk & scene.
		PxScene*				GetPxScene() const;
		PxPhysics*				GetPxSDK() const;
		const SimulationScale&	GetScale() const;
		PhysXCallback*			GetCallback() const;

	private:
		PxPhysics*					m_pxSDK;

		PxScene*					m_pxScene;
		PhysXCallback*				m_physXCallback;
		PxCpuDispatcher*			m_pxCpuDispatcher;

		SimulationScale				m_scale;

		PxControllerManager*		m_controllerPxMgr;

		CallbackPtr					m_contactCallback;

		Actors						m_actors;

		Shapes						m_shapes;

		MaterialPtr					m_defaultMaterial;
		Materials					m_materials;

		Joints						m_joints;

		Controllers					m_controllers;

		TimeListenerGroups			m_simulateListenerGroups;
		TimeListenerGroups			m_renderListenerGroups;

		TriggerEvents				m_triggerEvents;
	};

	namespace SceneExt
	{
		I3_EXPORT_PX Material& FindMaterial(Scene& scene, size_t idx);
		I3_EXPORT_PX Material& FindMaterial(Scene& scene, REAL32 dynamicFriction, REAL32 staticFriction, REAL32 restitution);
	}
}