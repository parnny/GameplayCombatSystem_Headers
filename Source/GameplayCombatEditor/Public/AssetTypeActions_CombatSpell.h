#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_CombatSpell : public FAssetTypeActions_Base
{
private:
	EAssetTypeCategories::Type AssetTypeCategory;
public:
	FAssetTypeActions_CombatSpell(EAssetTypeCategories::Type Category);

	// IAssetTypeActions Begin
	virtual FText GetName() const override {return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_CombatSpell", "CombatSpell"); }
	virtual FColor GetTypeColor() const override {return FColor(10, 10, 10); }
	virtual UClass* GetSupportedClass() const override;
//	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;
	// IAssetTypeActions End
};
