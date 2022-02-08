// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Aura.h"
#include "CombatantComponent.h"

#include "AuraComponent.generated.h"

/**
 * @brief 光环组件，用于管理光环
 * 在移除单个光环时，先将光环加入失效列表，触发光环Remove，在下一个组件Tick时清除，触发Destroy
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCOMBATSYSTEM_API UAuraComponent : public UActorComponent, public ICombatEventInterface
{
	GENERATED_BODY()	
public:	
	// Sets default values for this component's properties
	UAuraComponent();

	virtual void BeginDestroy() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Tick所有光环
	 * @param DeltaTime 时间变化
	 */
	UFUNCTION(BlueprintCallable)
	void TickAuras(float DeltaTime);

	// >>>>>>>>>>>> ICombatEventInterface
	virtual void HandleCombatEvent(const class UCombatEvent* CombatEvent) override;
	/**
	* @brief 创建光环，一般由创建者调用
	* @param AuraID 光环ID
	* @param AuraClass 光环类型
	* @param Lifetime 生命周期
	* @param Stack 层数
	* @param Creator 创建者,默认为光环组件所有者
	*/
	UFUNCTION(BlueprintCallable)
	UAura* CreateAura(const FName AuraID, const TSubclassOf<UAura> AuraClass, float Lifetime, int32 Stack);
	
	UFUNCTION(BlueprintCallable)
	UAura* ApplyAura(UAura* NewAura);
	/**
	 * @brief 移除光环, 将光环加入失效列表，在下一个组件Tick时清除
	 * @param AuraID 光环ID
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveAura(const FName AuraID);
	/**
	 * @brief 获得光环
	 * @return 光环实例
	 */
	UFUNCTION(BlueprintPure, meta=(DisplayName="FindAura(Name)"))
	UAura* FindAura(const FName AuraID);
	UFUNCTION(BlueprintPure, meta=(DisplayName="FindAura(Class)"))
	UAura* FindAuraByClass(const TSubclassOf<UAura> AuraClass);
	/**
	 * @brief 获得光环
	 * @param AuraID 光环ID
	 * @return 光环实例
	 */
	UFUNCTION(BlueprintPure)
	bool HasAura(const FName AuraID) const;
	/**
	 * @brief 清理所有光环，立刻清除
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveAllAuras();
private:
	const UAuraRefreshPolicy* GetRefreshPolicy(const UAura* Aura) const;
	const UAuraApplyPolicy* GetApplyPolicy(const UAura* Aura) const;
	
protected:
	/**
	 * @brief 光环实例容器
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName,UAura*> AuraMap;
	
	/**
	* @brief 光环的增加策略
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAuraApplyPolicy> ApplyPolicy;
	/**
	* @brief 光环的更新策略
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAuraRefreshPolicy> RefreshPolicy;
};
