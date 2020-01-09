using System;

namespace PostNetWork
{
	public abstract class BaseAction
	{
		public string klass;

		public BaseAction()
		{
			klass = this.GetType().Name;
		}

		public abstract void Excute();
	}

	public abstract class BaseActionResult : BaseAction
	{
		public override void Excute()
		{

		}
	}
}