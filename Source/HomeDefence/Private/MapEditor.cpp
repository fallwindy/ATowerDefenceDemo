
#include "HomeDefence/Public/MapEditor.h"
#include "HomeDefence/Public/TileBase.h"
#include "Kismet/KismetSystemLibrary.h"


AMapEditor::AMapEditor()
{
	PrimaryActorTick.bCanEverTick = true;
	Board.SetNum(120);
}


void AMapEditor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//SpawnTiles();
}

#if WITH_EDITOR
void AMapEditor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (!Board[0])
	{
		UE_LOG(LogTemp,Log,TEXT("posteditchangeproperty spawn"));
		SpawnTiles();
	}
	FindPath();
}
#endif


void AMapEditor::BeginPlay()
{
	Super::BeginPlay();
}


void AMapEditor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMapEditor::SpawnTiles()
{
	for (int i = 0; i < Max_X; i++)
	{
		for (int j = 0; j < Max_Y; j++)
		{
			FActorSpawnParameters Params;
			FVector location = FVector(i*100,j*100,0);
			auto CurTile = GetWorld()->SpawnActor<ATileBase>(TileClass,location,FRotator::ZeroRotator,Params);
			if (CurTile)
			{
				CurTile->X_Coorinate = i;
				CurTile->Y_Coordinate = j;
				//CurTile->TileType = Grass;
				 Board[i*12+j] = CurTile;
				//Board.Add(CurTile);
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("fail to spawn"));
			}
		}
	}
	 Start = Board[Max_Y*(Max_X-1)];
     End = Board[Max_Y-1];
	
}

void AMapEditor::FindPath()
{
	//if(Board.Num()==0)return;
	if(!Board[0])return;
	TArray<int> XDirection = {0,0,1,-1};
	TArray<int> YDirection = {1,-1,0,0};
	TMap<ATileBase*,ATileBase*> PreTile;
	//auto Start = Board[Max_Y*(Max_X-1)];
	//auto End = Board[Max_Y-1];
	if(Start->TileType!=Road || End->TileType!=Road)return;//路径不可达

	TArray<ATileBase*> AOpen;
	TArray<ATileBase*> AClose;
	TSet<ATileBase*> Visited;
	Start->Cost = 0;
	AOpen.Add(Start);
	Visited.Add(Start);
	auto Cur = Start;

	//DijkStra算法
	while (AOpen.Num()!=0)
	{
		//找到最小值
		int MinCost = INT_MAX;
		for (auto& OpenTile : AOpen)
		{
			MinCost = FMath::Min(MinCost,OpenTile->Cost);
		}
		//取出最小值
		ATileBase* MinestTile;
		for (auto& OpenTile : AOpen)
		{
			if (OpenTile->Cost == MinCost)
			{
				Cur = OpenTile;
				AClose.Add(OpenTile);
				MinestTile = OpenTile;
				break;
			}
		}
		AOpen.Remove(MinestTile);
		
		if (Cur==End)break;
		
		//用最小值去更新周围
		for (int i = 0; i < 4; ++i)
		{
			int x = Cur->X_Coorinate + XDirection[i];
			int y = Cur->Y_Coordinate + YDirection[i];
			if(x<0 || x>=Max_X || y<0 || y>=Max_Y) continue;
			auto TheNext = Board[x*Max_Y + y];
			if ( TheNext->TileType == Road && !Visited.Contains(TheNext) )
			{
				if (Cur->Cost+1 < TheNext->Cost)
				{
					TheNext->Cost = Cur->Cost+1;
					//PreTile[TheNext] = Cur;
					PreTile.Add(TheNext,Cur);
					AOpen.Add(TheNext);
					Visited.Add(TheNext);
				}
			}
		}
	}

	if (AClose.Last()!=End) return;

	TArray<ATileBase*> RePath;
	auto PathNode = AClose.Last();
	while (PathNode!=Start)
	{
		RePath.Add(PathNode);
		PathNode = PreTile[PathNode];
	}
	RePath.Add(Start);
	for (int i = RePath.Num()-1; i >= 0 ; i--)
	{
		Path.Add(RePath[i]);
	}
}

