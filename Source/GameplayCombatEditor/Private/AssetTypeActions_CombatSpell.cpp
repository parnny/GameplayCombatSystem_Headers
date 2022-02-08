
#include "AssetTypeActions_CombatSpell.h"

#include "Spell.h"

FAssetTypeActions_CombatSpell::FAssetTypeActions_CombatSpell(EAssetTypeCategories::Type Category)
{
	AssetTypeCategory = Category;
}

UClass* FAssetTypeActions_CombatSpell::GetSupportedClass() const
{
	return USpell::StaticClass();
}

uint32 FAssetTypeActions_CombatSpell::GetCategories()
{
	return AssetTypeCategory;
}
