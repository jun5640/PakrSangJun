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

	int CreateBlockCount = 0;       //새로 생성해야 할 블록 카운트
	int DropAnimaionCount = 0;

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

	private void Start()
	{
		m_MapLoad.SetBlock(MapName);
		SetCreateBlockPosition();
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
		if (MoveDisAble) return;

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
		if(overIndex + 1 == selectIndex ||
		   overIndex - 1 == selectIndex ||
		   overIndex - m_MapLoad.GetColCount() == selectIndex ||
		   overIndex + m_MapLoad.GetColCount() == selectIndex ||
		   overIndex - m_MapLoad.GetColCount() + 1 == selectIndex ||
		   overIndex + m_MapLoad.GetColCount() + 1 == selectIndex
		  )
		{
			return true;
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

		//GameObject temp = m_MapLoad.blocks[index1];
		//m_MapLoad.blocks[index1] = m_MapLoad.blocks[index2];
		//m_MapLoad.blocks[index2] = temp;

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
		
		//m_MapLoad.blocks[index2] = temp;

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
		DownMatchCheck();

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

			//
			// 드랍
			//
			DropBlock();

			// 
			// 흘러 내리기
			//

			while(WaterDrop())
			{

			}

			//
			// 매치 재검사.
			//
			StartCoroutine(ReMatchCheck());
			//
			// 블럭 재생성.
			//
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
	// 매치된 블럭을 풀에 반환 하고 비활성화 처리를 합니다.
	//
	void ReleaseBlock()	
	{
		for(int i = 0; i < MatchList.Count; i++)
		{
			BlockHive hiveinfo = MatchList[i].GetComponent<BlockHive>();

			BlockPool.ReturnPool(hiveinfo.blockobj.gameObject);
			hiveinfo.blockobj.gameObject.SetActive(false);
			hiveinfo.InitData();
		}

		MatchList.Clear();
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
						if(rowIndex % 2 == 0)
						{
							if(m_MapLoad.blocks[blockIndex - row] != null)
							{

							}
						}
						else
						{
							if (m_MapLoad.blocks[blockIndex - row + 1] != null)
							{

							}
						}
					}
					else
					{
						if (rowIndex % 2 == 0)
						{
							if (m_MapLoad.blocks[blockIndex + row] != null)
							{

							}
						}
						else
						{
							if (m_MapLoad.blocks[blockIndex + row + 1] != null)
							{

							}
						}
					}
				}
			}
		}




		return result;
	}

	int FindAbleWaterDropBlock(int index)
	{
		index--;

		if (index % m_MapLoad.GetColCount() == 0 || m_MapLoad.blocks[index] == null)
		{
			return -1;
		}
		else
		{
			if (m_MapLoad.blocks[index].GetComponent<BlockHive>().blockobj == null)
			{
				return FindAbleDropBlock(index);
			}
			else
			{
				return index;
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
	#endregion


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

	IEnumerator ReMatchCheck()
	{
		bool IsMatch;
		while(true)
		{
			if (DropAnimaionCount == 0)
			{
				IsMatch = MatchCheck();
				break;
			}
			yield return null;
		}

		if (!IsMatch)
		{
			//
			// 블럭 재생성
			//
#if UNITY_EDITOR
			Debug.Log("Create New Block");
#endif
			MoveDisAble = false;
		}
	}
}