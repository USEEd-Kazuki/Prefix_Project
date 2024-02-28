// Fill out your copyright notice in the Description page of Project Settings.


#include "PrefixUtility.h"
#include "EditorUtilityLibrary.h"

void UPrefixUtility::AddPrefixes()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			// �I�����ꂽ�I�u�W�F�N�g�̃N���X�ɑΉ�����prefix������
			const FString* Prefix = PrefixMap.Find(SelectedObject->GetClass());
			if (ensure(Prefix) && !Prefix->Equals(""))
			{
				FString OldName = SelectedObject->GetName();
				// �Â����O��prefix�Ŏn�܂��Ă��Ȃ��ꍇ�A�V�������O���쐬���A�A�Z�b�g�̖��O��ύX
				if (!OldName.StartsWith(*Prefix)) 
				{
					FString NewName = *Prefix + OldName;
					UEditorUtilityLibrary::RenameAsset(SelectedObject, NewName);
					++Counter;
				}
			}
			else 
			{
				// �N���X�ɑΉ�����v���t�B�b�N�X��������Ȃ��ꍇ�A�G���[���b�Z�[�W��\��
				PrintToScreen("Couldn't fid prefix for class" + SelectedObject->GetClass()->GetName(), FColor::Red);
			}
		}
	}

	GiveFeedback("Added prefix to", Counter);
}

void UPrefixUtility::PrintToScreen(FString Message, FColor Color)
{
	if (ensure(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, Color, Message);
	}
}

void UPrefixUtility::GiveFeedback(FString Method, uint32 Counter)
{
	FString Message = FString("No matching files found");
	FColor Color = Counter > 0 ? FColor::Green : FColor::Red;
	if (Counter > 0)
	{
		Message = Method.AppendChar(' ');
		Message.AppendInt(Counter);
		Message.Append(Counter == 1 ? TEXT(" file") : TEXT(" files"));
	}
	PrintToScreen(Message, Color);
}
