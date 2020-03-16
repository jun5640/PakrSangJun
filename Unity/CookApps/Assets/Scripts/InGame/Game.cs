using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Game : UIManagerBase
{
	static Game _instance = null;
	public MapLoad m_MapLoad;

	public ObjectPoolBase<GameObject> BlockPool = new ObjectPoolBase<GameObject>();

	GameObject SelectBlockObject = null;		//선택된 블록
	//GameObject OverBlockObject = null;      //블록이 선택되고 OverBlock일 경우.

	int SelectBlockIndex = -1;

	bool MoveDisAble = false;

	public List<GameObject> CreateBlockPosition = new List<GameObject>();
	public List<GameObject> MatchList = new List<GameObject>(); //매치 확정이 되어 반환 예정인 오브젝트 리스트.

	List<int> TempMatchListIndex = new List<int>();      //매치 검사 과정에서 연속된 수를 저장

	public string MapName;

	public int CreateBlockCount = 0;       //새로 생성해야 할 블록 카운트
	int DropAnimaionCount = 0;             //떨어지는 애니메이션이 끝나야 다음 플레이어의 움직임이 가능하다.
	public int Goal = 0;                           //목표 수.

	public static new Game instance
	{
		get { return _instance; }
	}

	private void OnEnable()
	{
		_instance = this;
	}

	private void Awake()
	{
		this.Setup();
	}

	public override void Setup()
	{
		base.Setup();
	}

	private void Update()
	{
		if (Input.GetKeyDown(KeyCode.Escape))
		{
			SceneManager.LoadScene("Menu");
		}
	}

	private void Start()
	{
		m_MapLoad.SetBlock(MapName);
		SetCreateBlockPosition();
		SetGoal();
	}

	void SetGoal()
	{
		for (int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			if (info.blockobj == null) continue;
			if (info.GetBlockInfo().type != Map.BLOCKTYPPE.NONE && info.GetBlockInfo().type != Map.BLOCKTYPPE.BLOCK)
			{
				Goal++;
			}
		}

		UIGame.instance.SetGoal(Goal);
	}

	//
	// 블록을 생성해서 아래로 내려주기 때문에 젤 꼭대기에 있는 하이브 블록만 저장한다.
	//
	void SetCreateBlockPosition()
	{
		int row = m_MapLoad.GetRowCount();
		int col = m_MapLoad.GetColCount();

		int interval = 0;

		for(int i = 0; i < row*col; i++)
		{
			if (i != 0 && i % row == 0)
			{
				if (CreateBlockPosition.Count != 0) break;
				interval += 7;
			}

			int index = (i * row) + interval;

			if(m_MapLoad.blocks[index] != null)
			{
				CreateBlockPosition.Add(m_MapLoad.blocks[index]);
			}
		}
	}

	public void SelectBlock(GameObject go, Map.BLOCKTYPPE type)
	{
		if (MoveDisAble || DropAnimaionCount != 0) return;

		if(MoveTypeCheck(type))
		{
			SelectBlockObject = go;
			SelectBlockIndex = m_MapLoad.GetBlockIndex(go);
		}
		else
		{
			SelectBlockObject = null;
			SelectBlockIndex = -1;
		}
	}

	public void MatchBlock(GameObject go, Map.BLOCKTYPPE type)
	{
		if(SelectBlockObject != null && MoveTypeCheck(type))
		{
			if(go != SelectBlockObject)
			{
				int index = m_MapLoad.GetBlockIndex(go);

				if(BlockMoveCheck(SelectBlockIndex, index))
				{
#if UNITY_EDITOR
					Debug.Log("Move Able!!!!!!!");
#endif
					StartCoroutine(SwapBlock(SelectBlockObject, go, SelectBlockIndex, index));
					UnSelectBlock();
				}
			}
		}
	}

	
	public bool MoveTypeCheck(Map.BLOCKTYPPE type)
	{
		if(type == Map.BLOCKTYPPE.BLOCK || 
		   type == Map.BLOCKTYPPE.TOP
		   )
		{
			return true;
		}

		return false;
	}

	public bool BlockMoveCheck(int selectIndex,int overIndex)
	{

		int row = m_MapLoad.GetRowCount();
		int rowcount = overIndex / row;

		if (rowcount % 2 == 0)
		{
			if (overIndex + 1 == selectIndex ||
			   overIndex - 1 == selectIndex ||
			   overIndex - m_MapLoad.GetColCount() == selectIndex ||
			   overIndex + m_MapLoad.GetColCount() == selectIndex ||
			   overIndex - m_MapLoad.GetColCount() - 1 == selectIndex ||
			   overIndex + m_MapLoad.GetColCount() - 1 == selectIndex
			  )
			{
				return true;
			}
		}
		else
		{
			if (overIndex + 1 == selectIndex ||
			   overIndex - 1 == selectIndex ||
			   overIndex - m_MapLoad.GetColCount() == selectIndex ||
			   overIndex + m_MapLoad.GetColCount() == selectIndex ||
			   overIndex - m_MapLoad.GetColCount() + 1 == selectIndex ||
			   overIndex + m_MapLoad.GetColCount() + 1 == selectIndex
			  )
			{
				return true;
			}
		}
		return false;
	}

	public void UnSelectBlock()
	{
		SelectBlockObject = null;
		//OverBlockObject = null;
		SelectBlockIndex = -1;
	}


	IEnumerator SwapBlock(GameObject go1, GameObject go2,int index1,int index2,bool MatchedCheck = false)
	{
		MoveDisAble = true;

		Transform tempparent = go1.transform.parent; 

		go1.transform.parent = go2.transform.parent;
		go2.transform.parent = tempparent; 

		Vector3 v1 = go1.transform.localPosition;
		Vector3 v2 = go2.transform.localPosition;

		float time = 0;

		go1.GetComponent<SpriteRenderer>().sortingOrder = 2;

		while(true)
		{
			time += Time.deltaTime;

			go1.transform.localPosition = Vector3.Lerp(v1, Vector3.zero, time);
			go2.transform.localPosition = Vector3.Lerp(v2, Vector3.zero, time);

			if (time > 1) break;
			yield return null;
		}

		go1.GetComponent<SpriteRenderer>().sortingOrder = 1;

		
		m_MapLoad.blocks[index1].GetComponent<BlockHive>().SetBlockObject(go2);
		m_MapLoad.blocks[index2].GetComponent<BlockHive>().SetBlockObject(go1);

		//
		// 판정 호출 하고 실패할 경우 다시 돌려야 함.
		//

		if (!MatchCheck() && !MatchedCheck)
		{
			StartCoroutine(SwapBlock(go2, go1, index1, index2, true));
		}
		
	}

	#region MatchCheckFunction

	bool MatchCheck()
	{
		CrossDownMatchCheck();
		CrossUpMatchCheck();
		DownMatchCheck();
		FourMatchCheck();

		if (MatchList.Count == 0)
		{
			MoveDisAble = false;
			return false;
		}
		else
		{
			//
			// 해당 블록 지우는 함수 추가.
			// 
			ReleaseBlock();
			ReleaseObs();	/// 장해물 목숨 감소 밑 제거 함수
			//
			// 드랍
			//
			DropBlock();


			//
			// 매치 재검사. 리매치 하기전에 생성을 해준다.
			//
			StartCoroutine(ReMatchCheck());

			

			return true;
		}

	}

	void DownMatchCheck()
	{
		for (int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			if (info.blockobj == null) continue;

			if (info.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
			{
				DownNextCheck(info.GetBlockInfo().color, i);
			}

			if (TempMatchListIndex.Count >= 3)
			{
				for (int n = 0; n < TempMatchListIndex.Count; n++)
				{
					if (!MatchList.Contains(m_MapLoad.blocks[TempMatchListIndex[n]]))
					{
						MatchList.Add(m_MapLoad.blocks[TempMatchListIndex[n]]);
					}
				}
			}

			TempMatchListIndex.Clear();
		}
	}

	void DownNextCheck(Map.BLOCKCOLOR color, int index)
	{
		int NextCheckIndex = index + 1;

		if (NextCheckIndex > m_MapLoad.GetRowCount() * m_MapLoad.GetColCount() || m_MapLoad.blocks[NextCheckIndex] == null || NextCheckIndex % m_MapLoad.GetRowCount() == 0)
		{
			TempMatchListIndex.Add(index);
			return;
		}

		BlockHive info = m_MapLoad.blocks[index].GetComponent<BlockHive>();
		BlockHive info2 = m_MapLoad.blocks[NextCheckIndex].GetComponent<BlockHive>();

		if (info2.blockobj == null)
		{
			TempMatchListIndex.Add(index);
			return;
		}

		if (info.GetBlockInfo().color == info2.GetBlockInfo().color && info2.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
		{
			TempMatchListIndex.Add(index);
			DownNextCheck(color, NextCheckIndex);
		}
		else
		{
			TempMatchListIndex.Add(index);
		}
	}

	void CrossDownMatchCheck()
	{
		for(int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			if (info.blockobj == null) continue;

			if (info.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
			{
				CrossDownNextCheck(info.GetBlockInfo().color, i);
			}

			if(TempMatchListIndex.Count >= 3)
			{
				for(int n = 0; n < TempMatchListIndex.Count; n++)
				{
					if (!MatchList.Contains(m_MapLoad.blocks[TempMatchListIndex[n]]))
					{
						MatchList.Add(m_MapLoad.blocks[TempMatchListIndex[n]]);
					}
				}			
			}

			TempMatchListIndex.Clear();
		}
	}

	void CrossDownNextCheck(Map.BLOCKCOLOR color,int index)
	{
		//
		// row 가 짝수면 같은 라인. row가 홀수면 대각선 아래 검사
		//

		int NextCheckIndex = index + m_MapLoad.GetRowCount() + (index / m_MapLoad.GetRowCount() % 2);

		if (NextCheckIndex > m_MapLoad.GetRowCount() * m_MapLoad.GetColCount() || m_MapLoad.blocks[NextCheckIndex] == null ) 
		{
			TempMatchListIndex.Add(index);
			return;
		}

		BlockHive info = m_MapLoad.blocks[index].GetComponent<BlockHive>();
		BlockHive info2 = m_MapLoad.blocks[NextCheckIndex].GetComponent<BlockHive>();

		if (info2.blockobj == null)
		{
			TempMatchListIndex.Add(index);
			return;
		}

		if (info.GetBlockInfo().color == info2.GetBlockInfo().color && info2.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
		{
			TempMatchListIndex.Add(index);
			CrossDownNextCheck(color, NextCheckIndex);
		}
		else
		{
			TempMatchListIndex.Add(index);
		}
	}

	//
	// 대각선 업방향
	//


	void CrossUpMatchCheck()
	{
		for (int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			if (info.blockobj == null) continue;

			if (info.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
			{
				CrossUpNextCheck(info.GetBlockInfo().color, i);
			}

			if (TempMatchListIndex.Count >= 3)
			{
				for (int n = 0; n < TempMatchListIndex.Count; n++)
				{
					if (!MatchList.Contains(m_MapLoad.blocks[TempMatchListIndex[n]]))
					{
						MatchList.Add(m_MapLoad.blocks[TempMatchListIndex[n]]);
					}
				}
			}

			TempMatchListIndex.Clear();
		}
	}

	void CrossUpNextCheck(Map.BLOCKCOLOR color, int index) //홀수일때 옆에꺼 (+col) 짝수일때 한칸 위 + (col - 1)
	{
		//
		// row 가 짝수면 같은 라인. row가 홀수면 대각선 아래 검사
		//

		int NextCheckIndex = index + m_MapLoad.GetRowCount() - (((index / m_MapLoad.GetRowCount()) + 1) % 2);

		if (NextCheckIndex > m_MapLoad.GetRowCount() * m_MapLoad.GetColCount() || m_MapLoad.blocks[NextCheckIndex] == null)
		{
			TempMatchListIndex.Add(index);
			return;
		}

		BlockHive info = m_MapLoad.blocks[index].GetComponent<BlockHive>();
		BlockHive info2 = m_MapLoad.blocks[NextCheckIndex].GetComponent<BlockHive>();

		if (info2.blockobj == null)
		{
			TempMatchListIndex.Add(index);
			return;
		}

		if (info.GetBlockInfo().color == info2.GetBlockInfo().color && info2.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
		{
			TempMatchListIndex.Add(index);
			CrossUpNextCheck(color, NextCheckIndex);
		}
		else
		{
			TempMatchListIndex.Add(index);
		}
	}

	void FourMatchCheck()
	{
		int row = m_MapLoad.GetRowCount();
		int col = m_MapLoad.GetColCount();
		for (int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			int rowcount = i / row;

			if (info.blockobj == null) continue;

			if (info.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK)
			{
				if (rowcount % 2 == 0)
				{
					int downIndex = i + 1; 
					int crossupIndex = i + col - 1; 
					int crossdownIndex = i + col;	
					int crossdown2Index = i + col + 1;	
					int tworownextIndex = i + (col*2);	

					GameObject down = null; 
					GameObject crossup = null; 
					GameObject crossdown = null; 
					GameObject crossdown2 = null; 
					GameObject tworownext = null; 

					if(downIndex > 0 && downIndex < row*col) down = m_MapLoad.blocks[downIndex];
					if (crossupIndex > 0 && crossupIndex < row * col) crossup = m_MapLoad.blocks[crossupIndex];
					if (crossdownIndex > 0 && crossdownIndex < row * col) crossdown = m_MapLoad.blocks[crossdownIndex];
					if (crossdown2Index > 0 && crossdown2Index < row * col) crossdown2 = m_MapLoad.blocks[crossdown2Index];
					if (tworownextIndex > 0 && tworownextIndex < row * col) tworownext = m_MapLoad.blocks[tworownextIndex];

					BlockHive hivedown = null;
					BlockHive hivecrossup = null;
					BlockHive hivecrossdown = null;
					BlockHive hivecrossdown2 = null;
					BlockHive hivetworownext = null;

					if (down != null)
					{
						hivedown = down.GetComponent<BlockHive>();
					}
					if(crossup != null)
					{
						hivecrossup = crossup.GetComponent<BlockHive>();
					}
					if (crossdown != null)
					{
						hivecrossdown = crossdown.GetComponent<BlockHive>();
					}
					if (crossdown2 != null)
					{
						hivecrossdown2 = crossdown2.GetComponent<BlockHive>();
					}
					if (tworownext != null)
					{
						hivetworownext = tworownext.GetComponent<BlockHive>();
					}

					if(FourMatchCheckColor(info,hivecrossup, hivecrossdown, hivetworownext)) 
					{
						TempMatchListIndex.Add(i);
						TempMatchListIndex.Add(crossupIndex);
						TempMatchListIndex.Add(crossdownIndex);
						TempMatchListIndex.Add(tworownextIndex);
					}
					if(FourMatchCheckColor(info, hivedown, hivecrossup, hivecrossdown)) 
					{
						TempMatchListIndex.Add(i);
						TempMatchListIndex.Add(downIndex);
						TempMatchListIndex.Add(crossupIndex);
						TempMatchListIndex.Add(crossdownIndex);
					}
					if(FourMatchCheckColor(info, hivedown, hivecrossdown, hivecrossdown2)) 
					{
						TempMatchListIndex.Add(i);
						TempMatchListIndex.Add(downIndex);
						TempMatchListIndex.Add(crossdownIndex);
						TempMatchListIndex.Add(crossdown2Index);
					}
				}
				else
				{
					int downIndex = i + 1;//18
					int crossupIndex = i + col;//24
					int crossdownIndex = i + col + 1;//25
					int crossdown2Index = i + col + 2;//26
					int tworownextIndex = i + (col * 2);//31

					GameObject down = null;
					GameObject crossup = null;
					GameObject crossdown = null;
					GameObject crossdown2 = null;
					GameObject tworownext = null;

					if (downIndex > 0 && downIndex < row * col) down = m_MapLoad.blocks[downIndex];
					if (crossupIndex > 0 && crossupIndex < row * col) crossup = m_MapLoad.blocks[crossupIndex];
					if (crossdownIndex > 0 && crossdownIndex < row * col) crossdown = m_MapLoad.blocks[crossdownIndex];
					if (crossdown2Index > 0 && crossdown2Index < row * col) crossdown2 = m_MapLoad.blocks[crossdown2Index];
					if (tworownextIndex > 0 && tworownextIndex < row * col) tworownext = m_MapLoad.blocks[tworownextIndex];


					BlockHive hivedown = null;
					BlockHive hivecrossup = null;
					BlockHive hivecrossdown = null;
					BlockHive hivecrossdown2 = null;
					BlockHive hivetworownext = null;

					if (down != null)
					{
						hivedown = down.GetComponent<BlockHive>();
					}
					if (crossup != null)
					{
						hivecrossup = crossup.GetComponent<BlockHive>();
					}
					if (crossdown != null)
					{
						hivecrossdown = crossdown.GetComponent<BlockHive>();
					}
					if (crossdown2 != null)
					{
						hivecrossdown2 = crossdown2.GetComponent<BlockHive>();
					}
					if (tworownext != null)
					{
						hivetworownext = tworownext.GetComponent<BlockHive>();
					}

					if (FourMatchCheckColor(info, hivecrossup, hivecrossdown, hivetworownext))//17 24 25 31
					{
						TempMatchListIndex.Add(i);
						TempMatchListIndex.Add(crossupIndex);
						TempMatchListIndex.Add(crossdownIndex);
						TempMatchListIndex.Add(tworownextIndex);
					}
					if (FourMatchCheckColor(info, hivedown, hivecrossup, hivecrossdown))
					{
						TempMatchListIndex.Add(i);
						TempMatchListIndex.Add(downIndex);
						TempMatchListIndex.Add(crossupIndex);
						TempMatchListIndex.Add(crossdownIndex);
					}
					if (FourMatchCheckColor(info, hivedown, hivecrossdown, hivecrossdown2))
					{
						TempMatchListIndex.Add(i);
						TempMatchListIndex.Add(downIndex);
						TempMatchListIndex.Add(crossdownIndex);
						TempMatchListIndex.Add(crossdown2Index);
					}
				}
			}

			if (TempMatchListIndex.Count >= 4)
			{
				for (int n = 0; n < TempMatchListIndex.Count; n++)
				{
					if (!MatchList.Contains(m_MapLoad.blocks[TempMatchListIndex[n]]))
					{
						MatchList.Add(m_MapLoad.blocks[TempMatchListIndex[n]]);
					}
				}
			}

			TempMatchListIndex.Clear();
		}
	}

	bool FourMatchCheckColor(BlockHive hive1, BlockHive hive2, BlockHive hive3, BlockHive hive4)
	{
		if (hive1 != null &&
			hive2 != null &&
			hive3 != null &&
			hive4 != null &&
			hive1.blockobj != null &&
			hive2.blockobj != null &&
			hive3.blockobj != null &&
			hive4.blockobj != null &&
			hive1.GetBlockInfo().color == hive2.GetBlockInfo().color &&
			hive1.GetBlockInfo().color == hive3.GetBlockInfo().color &&
			hive1.GetBlockInfo().color == hive4.GetBlockInfo().color &&
			hive1.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK &&
			hive2.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK &&
			hive3.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK &&
			hive4.GetBlockInfo().type == Map.BLOCKTYPPE.BLOCK 
			)
		{
			return true;
		}
		return false;
	}

	//
	// 매치된 블럭을 풀에 반환 하고 비활성화 처리를 합니다.
	//
	void ReleaseBlock()	
	{
		CreateBlockCount += MatchList.Count;

		for(int i = 0; i < MatchList.Count; i++)
		{
			BlockHive hiveinfo = MatchList[i].GetComponent<BlockHive>();

			BlockPool.ReturnPool(hiveinfo.blockobj.gameObject);
			hiveinfo.blockobj.gameObject.SetActive(false);
			hiveinfo.InitData();
		}

		MatchList.Clear();
	}

	void ReleaseObs()
	{
		//
		// 팽이 주변에 빈공간이 있다면 주변에서 매치가 되었으므로 다이카운트를 낮춰 준다.
		//
		for (int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			if (info.blockobj == null) continue;
			if (info.GetBlockInfo().type != Map.BLOCKTYPPE.NONE && info.GetBlockInfo().type != Map.BLOCKTYPPE.BLOCK)
			{
				if (ObsCheck(i))
				{
					info.GetBlockInfo().DieCount--;
				}
			}
		}

		//
		// 다이카운트가 0이하인 장해물을 제거한다.
		//
		for (int i = 0; i < m_MapLoad.blocks.Length; i++)
		{
			if (m_MapLoad.blocks[i] == null) continue;

			BlockHive info = m_MapLoad.blocks[i].GetComponent<BlockHive>();

			if (info.blockobj == null) continue;

			if (info.blockobj == null) continue;

			if (info.GetBlockInfo().type != Map.BLOCKTYPPE.NONE && info.GetBlockInfo().type != Map.BLOCKTYPPE.BLOCK)
			{
				if(info.GetBlockInfo().DieCount <= 0)
				{
					BlockPool.ReturnPool(info.blockobj.gameObject);
					info.blockobj.gameObject.SetActive(false);
					info.InitData();
					CreateBlockCount++;
					Goal--;
					UIGame.instance.SetGoal(Goal);
				}
			}
		}
	}


	public bool ObsCheck(int index)
	{

		int row = m_MapLoad.GetRowCount();
		int col = m_MapLoad.GetColCount();
		int rowcount = index / row;

		if (rowcount % 2 == 0)
		{
			int index1 = index + 1;
			int index2 = index - 1;
			int index3 = index - m_MapLoad.GetColCount();
			int index4 = index + m_MapLoad.GetColCount();
			int index5 = index - m_MapLoad.GetColCount() - 1;
			int index6 = index + m_MapLoad.GetColCount() - 1;

			GameObject go1 = null;
			GameObject go2 = null;
			GameObject go3 = null;
			GameObject go4 = null;
			GameObject go5 = null;
			GameObject go6 = null;

			if(index1 >= 0 && index1 < row*col)go1 = m_MapLoad.blocks[index1];
			if (index2 >= 0 && index2 < row * col) go2 = m_MapLoad.blocks[index2];
			if (index3 >= 0 && index3 < row * col) go3 = m_MapLoad.blocks[index3];
			if (index4 >= 0 && index4 < row * col) go4 = m_MapLoad.blocks[index4];
			if (index5 >= 0 && index5 < row * col) go5 = m_MapLoad.blocks[index5];
			if (index6 >= 0 && index6 < row * col) go6 = m_MapLoad.blocks[index6];

			if (go1 != null && go1.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go2 != null && go2.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go3 != null && go3.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go4 != null && go4.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go5 != null && go5.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go6 != null && go6.GetComponent<BlockHive>().blockobj == null) return true;
		}
		else
		{
			int index1 = index + 1;
			int index2 = index - 1;
			int index3 = index - m_MapLoad.GetColCount();
			int index4 = index + m_MapLoad.GetColCount();
			int index5 = index - m_MapLoad.GetColCount() + 1;
			int index6 = index + m_MapLoad.GetColCount() + 1;

			GameObject go1 = null;
			GameObject go2 = null;
			GameObject go3 = null;
			GameObject go4 = null;
			GameObject go5 = null;
			GameObject go6 = null;

			if (index1 >= 0 && index1 < row * col) go1 = m_MapLoad.blocks[index1];
			if (index2 >= 0 && index2 < row * col) go2 = m_MapLoad.blocks[index2];
			if (index3 >= 0 && index3 < row * col) go3 = m_MapLoad.blocks[index3];
			if (index4 >= 0 && index4 < row * col) go4 = m_MapLoad.blocks[index4];
			if (index5 >= 0 && index5 < row * col) go5 = m_MapLoad.blocks[index5];
			if (index6 >= 0 && index6 < row * col) go6 = m_MapLoad.blocks[index6];

			if (go1 != null && go1.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go2 != null && go2.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go3 != null && go3.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go4 != null && go4.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go5 != null && go5.GetComponent<BlockHive>().blockobj == null) return true;
			else if (go6 != null && go6.GetComponent<BlockHive>().blockobj == null) return true;
		}

		return false;
	}

	//
	// 풀이 반환되어 빈 공간을 떨어지는 형태로 채워 줍니다.
	//

	void DropBlock()
	{
		int col = m_MapLoad.GetColCount();
		int row = m_MapLoad.GetRowCount();

		int Interval = col;
		int index = 0;

		for(int i = 0; i < row * col; i++)
		{
			if (i % col == 0) index++;

			int aryIndex = (index * Interval) - 1;
			aryIndex = (aryIndex) - (i % col);

			GameObject go = m_MapLoad.blocks[aryIndex];

			if (go == null) continue;

			if(go.GetComponent<BlockHive>().blockobj == null)
			{
				if(aryIndex % col != 0 && m_MapLoad.blocks[aryIndex - 1] != null)
				{
					if(m_MapLoad.blocks[aryIndex - 1].GetComponent<BlockHive>().blockobj == null)
					{
						int result = FindAbleDropBlock(aryIndex - 1);

						if (result != -1)
						{
							GameObject BlockObj = m_MapLoad.blocks[result].GetComponent<BlockHive>().blockobj.gameObject;
							m_MapLoad.blocks[result].GetComponent<BlockHive>().InitData(false);
							BlockObj.transform.parent = go.transform;
							StartCoroutine(Drop(BlockObj, go,aryIndex));
						}
					}
					else
					{
						GameObject BlockObj = m_MapLoad.blocks[aryIndex - 1].GetComponent<BlockHive>().blockobj.gameObject;
						m_MapLoad.blocks[aryIndex - 1].GetComponent<BlockHive>().InitData(false);
						BlockObj.transform.parent = go.transform;
						StartCoroutine(Drop(BlockObj, go,aryIndex));
					}
				}
			}
		}
	}

	bool WaterDrop()
	{
		DropBlock();

		if (DropAnimaionCount != 0)
		{
			return true;
		}

		

		bool result = false;


		int col = m_MapLoad.GetColCount();
		int row = m_MapLoad.GetRowCount();

		int Interval = col;
		int index = 0;

		List<int> createPosIndexs = new List<int>();
		for(int i = 0; i < CreateBlockPosition.Count; i++)
		{
			createPosIndexs.Add(m_MapLoad.GetHiveBlockIndex(CreateBlockPosition[i]) / row);
		}
		
		for (int i = 0; i < row * col; i++)
		{
			if (i % col == 0) index++;

			int aryIndex = (index * Interval) - 1;
			aryIndex = (aryIndex) - (i % col);

			GameObject go = m_MapLoad.blocks[aryIndex];

			if (go == null) continue;

			if (go.GetComponent<BlockHive>().blockobj == null)
			{
				int blockIndex = m_MapLoad.GetHiveBlockIndex(go);
				int rowIndex = blockIndex / row;
				

				if (!createPosIndexs.Contains(rowIndex))
				{
					if(createPosIndexs[createPosIndexs.Count - 1] < rowIndex)
					{
						if(rowIndex % 2 == 1)
						{
							if(m_MapLoad.blocks[blockIndex - row] != null && m_MapLoad.blocks[blockIndex - row].GetComponent<BlockHive>().blockobj != null)
							{
								int resultValue = FindAbleWaterDropBlock(blockIndex - row);

								if (resultValue != -1)
								{
									Vector3 path = FindPath(blockIndex,false);

									GameObject BlockObj = m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().blockobj.gameObject;
									m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().InitData(false);
									BlockObj.transform.parent = go.transform;
									StartCoroutine(WaterDropAnimation(BlockObj, go, aryIndex, path));

									return true;// result = true;
								}
							}
						}
						else
						{
							if (m_MapLoad.blocks[blockIndex - row - 1] != null && m_MapLoad.blocks[blockIndex - row - 1].GetComponent<BlockHive>().blockobj != null)
							{
								int resultValue = FindAbleWaterDropBlock(blockIndex - row - 1);

								if (resultValue != -1)
								{
									Vector3 path = FindPath(blockIndex,false);

									GameObject BlockObj = m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().blockobj.gameObject;
									m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().InitData(false);
									BlockObj.transform.parent = go.transform;
									StartCoroutine(WaterDropAnimation(BlockObj, go, aryIndex, path));

									return true; //result = true;
								}
							}
						}
					}
					else if(createPosIndexs[createPosIndexs.Count - 1] > rowIndex)
					{
						if (rowIndex % 2 == 1)
						{
							if (m_MapLoad.blocks[blockIndex + row] != null && m_MapLoad.blocks[blockIndex + row].GetComponent<BlockHive>().blockobj != null)
							{
								int resultValue = FindAbleWaterDropBlock(blockIndex + row);

								if (resultValue != -1)
								{
									Vector3 path = FindPath(blockIndex,true);

									GameObject BlockObj = m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().blockobj.gameObject;
									m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().InitData(false);
									BlockObj.transform.parent = go.transform;
									StartCoroutine(WaterDropAnimation(BlockObj, go, aryIndex, path));

									return true; //result = true;

								}
							}
						}
						else
						{
							if (m_MapLoad.blocks[blockIndex + row - 1] != null && m_MapLoad.blocks[blockIndex + row - 1].GetComponent<BlockHive>().blockobj != null)
							{
								int resultValue = FindAbleWaterDropBlock(blockIndex + row - 1);

								if (resultValue != -1)
								{
									Vector3 path = FindPath(blockIndex,true);

									GameObject BlockObj = m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().blockobj.gameObject;
									m_MapLoad.blocks[resultValue].GetComponent<BlockHive>().InitData(false);
									BlockObj.transform.parent = go.transform;
									StartCoroutine(WaterDropAnimation(BlockObj, go, aryIndex, path));

									return true; //result = true;
								}
							}
						}
					}
				}
			}
		}




		return result;
	}

	Vector3 FindPath(int index,bool isleft) 
	{

		int row = m_MapLoad.GetRowCount(); ;
		int rowIndex = index / row;

		if (rowIndex % 2 == 1 && isleft)	// 홀수
		{
			if (m_MapLoad.blocks[index + row] != null && m_MapLoad.blocks[index + row].GetComponent<BlockHive>().blockobj == null)
			{
				return m_MapLoad.blocks[index+1].gameObject.transform.position;
			}
		}
		else if(rowIndex % 2 == 0 && isleft)
		{
			if (m_MapLoad.blocks[index + row - 1] != null && m_MapLoad.blocks[index + row - 1].GetComponent<BlockHive>().blockobj == null)
			{
				return m_MapLoad.blocks[index + 1].gameObject.transform.position;
			}
		}
		else if (rowIndex % 2 == 1 && !isleft)	// 홀수 
		{
			if (m_MapLoad.blocks[index - row] != null && m_MapLoad.blocks[index - row].GetComponent<BlockHive>().blockobj == null)
			{
				return m_MapLoad.blocks[index + 1].gameObject.transform.position;
			}
		}
		else if (rowIndex % 2 == 0 && !isleft)
		{
			if (m_MapLoad.blocks[index - row - 1] != null && m_MapLoad.blocks[index - row - 1].GetComponent<BlockHive>().blockobj == null)
			{
				return m_MapLoad.blocks[index + 1].gameObject.transform.position;
			}
		}


		if (index % m_MapLoad.GetColCount() == 0 || m_MapLoad.blocks[index] == null)
		{
			if(index % m_MapLoad.GetColCount() == 0 && m_MapLoad.blocks[index] != null)
			{
				return m_MapLoad.blocks[index].gameObject.transform.position;
			}
			else
			{
				return m_MapLoad.blocks[index + 1].gameObject.transform.position;
			}
		}
		else
		{
			return FindPath(index - 1,isleft);
		}
	}

	int FindAbleWaterDropBlock(int index)
	{
		if (index % m_MapLoad.GetColCount() == 0 || m_MapLoad.blocks[index] == null)
		{
			if(index % m_MapLoad.GetColCount() == 0)
			{
				if(m_MapLoad.blocks[index] == null || m_MapLoad.blocks[index].GetComponent<BlockHive>().blockobj == null)
				{
					return index + 1;
				}
				else
				{
					return index;
				}
			}

			return index + 1;
		}
		else
		{
			if (m_MapLoad.blocks[index].GetComponent<BlockHive>().blockobj == null)
			{
				return index + 1;
			}
			else
			{
				return FindAbleWaterDropBlock(index - 1);
			}
		}
	}

	int FindAbleDropBlock(int index)
	{
		index--;

		if(index % m_MapLoad.GetColCount() == 0 || m_MapLoad.blocks[index] == null)
		{
			return -1;
		}
		else
		{
			if(m_MapLoad.blocks[index].GetComponent<BlockHive>().blockobj == null)
			{
				return FindAbleDropBlock(index);
			}
			else
			{
				return index;
			}
		}
	}
	


	IEnumerator Drop(GameObject BlockObj, GameObject BlockHive,int index)
	{
		DropAnimaionCount++;

		Vector3 v1 = BlockObj.transform.localPosition;

		float time = 0;

		int speed = (index % m_MapLoad.GetColCount()) + (index / m_MapLoad.GetColCount()); 
		
		while (true)
		{
			time += Time.deltaTime * speed;

			BlockObj.transform.localPosition = Vector3.Lerp(v1, Vector3.zero, time);

			if (time > 1) break;
			yield return null;
		}

		BlockHive.GetComponent<BlockHive>().SetBlockObject(BlockObj);

		DropAnimaionCount--;
	}

	IEnumerator WaterDropAnimation(GameObject BlockObj, GameObject BlockHive, int index,Vector3 path)
	{
		DropAnimaionCount++;

		Vector3 v1 = BlockObj.transform.position;

		float time = 0;

		int speed = (index / m_MapLoad.GetColCount()) - (m_MapLoad.GetColCount() - 1) / 2;
		speed = Mathf.Abs(speed) + 1;
		speed = speed * 3;

		while (true)
		{
			time += Time.deltaTime * speed;

			BlockObj.transform.position = Vector3.Lerp(v1, path, time);

			if (time > 1) break;
			yield return null;
		}

		time = 0;

		v1 = BlockObj.transform.localPosition;

		while (true)
		{
			time += Time.deltaTime * speed;

			BlockObj.transform.localPosition = Vector3.Lerp(v1, Vector3.zero, time);

			if (time > 1) break;
			yield return null;
		}

		BlockHive.GetComponent<BlockHive>().SetBlockObject(BlockObj);

		DropAnimaionCount--;
	}

	IEnumerator ReMatchCheck()
	{
		bool IsMatch;
		while(true)
		{
			if (DropAnimaionCount == 0)
			{
				if (!WaterDrop())
				{
					IsMatch = MatchCheck();
					break;
				}
			}
			yield return null;
		}

		if (!IsMatch)
		{
			//
			// 블럭 재생성
			//
			StartCoroutine(CreateBlock());

#if UNITY_EDITOR
			Debug.Log("Create New Block");
#endif
			//
		}
	}


	IEnumerator CreateBlock()
	{
		while(true)
		{
			if (CreateBlockCount == 0) break;
			if (DropAnimaionCount == 0)
			{
				GameObject go = BlockPool.GetPool();
				
				BlockHive hiveinfo = CreateBlockPosition[0].GetComponent<BlockHive>();
				hiveinfo.SetBlockObject(go);
				hiveinfo.SetBlockType(Map.BLOCKTYPPE.BLOCK);
				hiveinfo.SetBlockColor((Map.BLOCKCOLOR)GetRandoomColor());
				go.transform.parent = CreateBlockPosition[0].transform;
				go.transform.localPosition = Vector3.zero;
				go.SetActive(true);

				CreateBlockCount--;

				DropBlock();
				while (true)
				{
					if (DropAnimaionCount == 0)
					{
						if (!WaterDrop())
						{
							break;
						}
					}
					yield return null;
				}

				MatchCheck();

				if (CreateBlockCount <= 0)
				{
					break;
				}
			}

			yield return null;
		}

		MoveDisAble = false;
	}

	int GetRandoomColor()
	{
		return (int)Random.Range(1, 6);
	}

	#endregion
}