#pragma once

#include "i3PxCallback.h"

namespace i3Px
{
	struct I3_EXPORT_PX ActorDesc
	{
		i3::string	name;
		CallbackPtr	contactCallback;
		bool		isVisualizationEnable;
		bool		isGravityEnable;
		bool		isSendingSleepNotifiesEnable;
		bool		isSimulationEnable;
		UINT8		dominanceGroup;
	};

	I3_EXPORT_PX void InitializeActorDesc(ActorDesc& desc);

	class I3_EXPORT_PX Actor
	{
	public:
		Actor();
		explicit Actor(Scene* scene);
		virtual ~Actor() = 0;

		virtual void						SetName(const char* name);
		virtual const char*					GetName() const;

		virtual void						SetContactCallback(CallbackPtr cb);
		virtual CallbackPtr					GetContactCallback() const;

		virtual void						EnableVisualization(bool ok);
		virtual bool						IsVisualizationEnable() const;
		
		virtual void						EnableGravity(bool ok);
		virtual bool						IsGravityEnable() const;	

		virtual void						EnableSendingSleepNotifies(bool ok);
		virtual bool						IsSendingSleepNotifiesEnable() const;

		virtual void						EnableSimulation(bool ok);
		virtual bool						IsSimulationEnable() const;				

		virtual void						SetDominanceGroup(UINT8 group);
		virtual UINT8						GetDominanceGroup() const;

		virtual void						SetPxActor(PxActor* actor, Scene* scene);
		virtual PxActor*					GetPxActor() const;
		virtual void						DetachPxActor();

		virtual Enums::Actor::Type			GetType() const = 0;
		virtual bool						IsKindOf(const char* name) const;

		void* userData;

	protected:
		void _Initialize(const ActorDesc& desc, Scene* scene);

		Scene* m_scene;
		PxActor* m_actorPx;
		CallbackPtr m_contactCallback;
	};

	namespace ActorExt
	{
		I3_EXPORT_PX void RetrieveActorDesc(const Actor& actor, ActorDesc& out);
	}
}