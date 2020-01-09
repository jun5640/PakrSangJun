using System;
using System.Collections;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Linq;

namespace PostNetWork
{
	public class JsonToActionConverter : CustomCreationConverter<BaseAction>
	{
		public override Object ReadJson(JsonReader reader, Type objectType, Object existingValue, JsonSerializer serializer)
		{
			JObject jObject = JObject.Load(reader);

			BaseAction retValue = Create(objectType, jObject);

			if (retValue != null)
			{
				serializer.NullValueHandling = NullValueHandling.Ignore;
				serializer.Populate(jObject.CreateReader(), retValue);
			}

			return retValue;
		}

		public override BaseAction Create(Type objectType)
		{
			throw new NotImplementedException();
		}

		private BaseAction Create(Type objectType, JObject jObject)
		{
			BaseAction retValue = null;

			JToken Value = jObject["klass"];
			if (Value != null && Value.Type == JTokenType.String)
			{
				Type t = Type.GetType("PostNetWork." + Value.ToString());

				retValue = Activator.CreateInstance(t) as BaseAction;
			}
			return retValue;
		}
	}
}
