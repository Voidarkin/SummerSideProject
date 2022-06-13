#include "ItemDatabase.h"
#include "ItemData.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/DataAsset.h"
#include <string>

UItemDatabase::UItemDatabase()
{
	//	Items are all created here

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	// Must wait until all assets are discovered before populating list of other GameInfoBase assets.
	if (AssetRegistry.IsLoadingAssets()) {
		AssetRegistry.OnFilesLoaded().AddUObject(this, &UItemDatabase::OnRegistryLoaded);
	}
	else {
		OnRegistryLoaded();
	}

}

void UItemDatabase::OnRegistryLoaded()
{

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.ClassNames = { TEXT("Blueprint") }; //MyPrimaryDataAsset
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> AssetList;
	// This data could be stored as static and processed in Default___CharacterClass's UObject,
	// but I think the performance hit is negligible and it's easier this way.   Blueprint'/Game/BP_MyMyPrimaryDataAsset.BP_MyMyPrimaryDataAsset'
	AssetRegistry.GetAssets(Filter, AssetList);

	TArray<UItemData*> MyTArray;
	//Blueprint'/Game/BP_MyMyPrimaryDataAsset.BP_MyMyPrimaryDataAsset'
	std::string PathName = "Blueprint'";
	////////////////////////
	for (const FAssetData& Asset : AssetList) {
		FString AssetFullPath(PathName.c_str() + Asset.ObjectPath.ToString() + "'");

		auto dataAsset = StaticLoadObject(UObject::StaticClass(), NULL, *AssetFullPath);

		UBlueprint* bp = Cast<UBlueprint>(dataAsset);
		TSubclassOf<class UItemData> whatIWant = (UClass*)bp->GeneratedClass;

		//Testing if successfull - setting mesh or printing error
		if (whatIWant)
		{
			if (whatIWant->ClassDefaultObject->IsA<UItemData>()) { //IsChildOf(UMyPrimaryDataAsset::StaticClass()

				UItemData* MyAsset = Cast<UItemData>(whatIWant->ClassDefaultObject);// NewObject<UMyPrimaryDataAsset>(whatIWant->ClassDefaultObject);
				if (MyAsset->GetItemName() != "ItemTemplate") { //Ignore my template
					Database.Add(MyAsset);
					UE_LOG(LogTemp, Error, TEXT(" loaded"));
				}
			}
		}
	}
}

UItemData* UItemDatabase::GetItem(FString pName)
{
	for (int i = 0; i < Database.Max(); i++)
	{
		if (Database[i]->GetItemName() == pName)
		{
			return Database[i];
		}
	}
	return nullptr;
}
