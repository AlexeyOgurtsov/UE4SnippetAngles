#include "Tests/AutomationCommon.h"
#include "Math/UnrealMathUtility.h"

DEFINE_SPEC(AnglesSpec, "Angles", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::ApplicationContextMask)

void AnglesSpec::Define()
{
	Describe("FixedTurn", [this]() {
		It("Should increment angle to the last, when the angle from first to second is less then 180", [this]()
		{
			constexpr float CurrentAngle = 45;
			constexpr float DesiredAngle = 45 + 30;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = CurrentAngle + DeltaRate;
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should clamp the result angle is the desired angle is reached, but delta rate is greater than the rest", [this]()
		{
			constexpr float CurrentAngle = 45;
			constexpr float DesiredAngle = 50;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = DesiredAngle;
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should correctly work with winded angles and the RESULT must be UNWINDED(!)", [this]()
		{
			constexpr float CurrentAngle = 360 + 45;
			constexpr float DesiredAngle = 360 + 45 + 30;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = FMath::UnwindDegrees(CurrentAngle + DeltaRate);
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should correctly work when the current angle is winded, and the desired angle is NOT", [this]()
		{
			constexpr float CurrentAngle = 360 + 10;
			constexpr float DesiredAngle = 45;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = FMath::UnwindDegrees(CurrentAngle + DeltaRate);
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should correctly work when the desired angle is winded, and the current angle is NOT", [this]()
		{
			constexpr float CurrentAngle = 10;
			constexpr float DesiredAngle = 360 + 45;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = FMath::UnwindDegrees(CurrentAngle + DeltaRate);
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should correctly handle clamping with winded angles and the result must be unwinded", [this]()
		{
			constexpr float CurrentAngle = 360 + 45;
			constexpr float DesiredAngle = 360 + 50;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = FMath::UnwindDegrees(DesiredAngle);
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should correctly work when the first angle is negative", [this]()
		{
			constexpr float CurrentAngle = -20;
			constexpr float DesiredAngle = 30;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = (360 + CurrentAngle) + DeltaRate;
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should correctly work when both angles are negative", [this]()
		{
			constexpr float CurrentAngle = -20;
			constexpr float DesiredAngle = -10;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = (360 + CurrentAngle) + DeltaRate;
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should increment angle to the last EVER when delta rate is negative(!), when the angle from first to second is less then 180", [this]()
		{
			constexpr float CurrentAngle = 45;
			constexpr float DesiredAngle = 45 + 30;
			constexpr float DeltaRate = -10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = CurrentAngle + FMath::Abs(DeltaRate);
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});

		It("Should decrement angle from second to first, when the angle from the first to second is more then 180", [this]()
		{
			constexpr float CurrentAngle = 45 + 30;
			constexpr float DesiredAngle = 45;
			constexpr float DeltaRate = 10;
			const float NewAngle = FMath::FixedTurn(CurrentAngle, DesiredAngle, DeltaRate);
			const float ExpectedNewAngle = CurrentAngle - DeltaRate;
			TestEqual("FixedTurn", NewAngle, ExpectedNewAngle);
		});
	});
}
