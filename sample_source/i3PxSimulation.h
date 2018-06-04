#pragma once

#include "i3PxFilterData.h"
#include "i3PxSimulationFilter.h"

namespace i3Px
{
	namespace Simulation
	{
		typedef PxFilterFlags (*CallbackFunc)(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
											  PxFilterObjectAttributes attributes1, PxFilterData filterData1,
											  PxPairFlags& pairFlags,
											  const void* constantBlock, PxU32 constantBlockSize);

		I3_EXPORT_PX CallbackFunc GetDefaultCallback();

		namespace Nx	// 2.0 버전 호환 버전.
		{
			typedef Flags<INT32, UINT16> FilterGroup16;

			struct I3_EXPORT_PX FilteringGroups
			{
				FilterGroup16 groups0, groups1, groups2, groups3;
			};

			I3_EXPORT_PX void InitializeFilteringGroups(FilteringGroups& src);
			I3_EXPORT_PX bool operator==(const FilteringGroups& filter0, const FilteringGroups& filter1);
			I3_EXPORT_PX bool operator!=(const FilteringGroups& filter0, const FilteringGroups& filter1);

			struct I3_EXPORT_PX Groups
			{
				// collision groups(0 ~ 32). see Lesson 109 - Collision Groups.
				UINT32 group;	

				// secondary collision group(filtering masks). see Lesson 110 - Collision Filtering.
				FilteringGroups filtering;

				// reserve.
				UINT32 reserve;
			};

			I3_EXPORT_PX void		InitializeGroups(Groups& src);
			I3_EXPORT_PX FilterData ToFilterData(const Groups& src);
			I3_EXPORT_PX Groups		ToGroups(const FilterData& src);
			I3_EXPORT_PX bool		IsGroupsValid(const Groups& src);
			I3_EXPORT_PX bool		operator==(const Groups& group0, const Groups& group1);
			I3_EXPORT_PX bool		operator!=(const Groups& group0, const Groups& group1);

			struct I3_EXPORT_PX FilterOp
			{
				enum Enum
				{
					AND,
					OR,
					XOR,
					NAND,
					NOR,
					NXOR,
					SWAP_AND,
				};
			};

			I3_EXPORT_PX void	SetGroupCollisionFlag(UINT32 group0, UINT32 group1, bool enable);
			I3_EXPORT_PX bool	GetGroupCollisionFlag(UINT32 gorup0, UINT32 group1);
			I3_EXPORT_PX void	ClearGroupCollisionFlags();

			I3_EXPORT_PX void	SetGroup(Actor& actor, UINT32 group);
			I3_EXPORT_PX UINT32	GetGroup(const Actor& actor);

			I3_EXPORT_PX void	SetGroupsMask(Actor& actor, FilteringGroups groups);

			I3_EXPORT_PX void	SetFilterEquation(const FilterOp::Enum& op0, const FilterOp::Enum& op1, const FilterOp::Enum& op2,
												  const FilteringGroups& K0, const FilteringGroups& K1, bool result);

			I3_EXPORT_PX void	SetFilterOps(const FilterOp::Enum& op0, const FilterOp::Enum& op1, const FilterOp::Enum& op2);
			I3_EXPORT_PX void	SetFilterBool(bool result);
			I3_EXPORT_PX void	SetFilterConstant(const FilteringGroups& k0, const FilteringGroups& k1);

			I3_EXPORT_PX void	SetActorPairFlags(const Actor& a0, const Actor& a1, PxPairFlags flags);
			I3_EXPORT_PX bool	GetActorPairFlags(const Actor& a0, const Actor& a1, PxPairFlags& out);

			I3_EXPORT_PX void	SetShapePairFlags(const Shape& s0, const Shape& s1, PxPairFlags flags);
			I3_EXPORT_PX bool	GetShapePairFlags(const Shape& s0, const Shape& s1, PxPairFlags& out);

			I3_EXPORT_PX void	SetActorGroupPairFlags(UINT32 groupA0, UINT32 groupA1, PxPairFlags flags);
			I3_EXPORT_PX bool	GetActorGroupPairFlags(UINT32 groupA0, UINT32 groupA1, PxPairFlags& out);

			I3_EXPORT_PX CallbackFunc GetCallback();

			I3_EXPORT_PX PxFilterFlags CheckPairFlags(const PairFound& pair);
		}
	}
}