package simulator.factories;

import org.json.JSONObject;

import simulator.misc.Vector2D;
import simulator.model.ForceLaws;
import simulator.model.MovingTowardsTwoFixedPoints;

public class MovingTowardsTwoFixedPointsBuilder extends Builder<ForceLaws>{

	private double g1, g2;
	private Vector2D c1, c2;
	
	public MovingTowardsTwoFixedPointsBuilder() {
		super("mt2fp", "Moving Towards two fixedpoints");
		
	}

	@Override
	protected ForceLaws createInstance(JSONObject data) {
		
		ForceLaws f;
		
	
		this.c1 = tieneDataVec(data, "c1");
		this.c2 = tieneDataVec(data, "c2");
		this.g1 = tieneDataDoub(data, "g1");
		this.g2 = tieneDataDoub(data, "g2");
		
		f = new MovingTowardsTwoFixedPoints(c1, c2, g1, g2);
		
		return f;
	}
	
	public Vector2D tieneDataVec(JSONObject data, String aux) {
		
		Vector2D vect = null;
		
		if(data.has(aux)) {
			
			double v1 = data.getJSONArray(aux).getDouble(0);
			double v2 = data.getJSONArray(aux).getDouble(1);

			if(data.getJSONArray(aux).length() > 2) {
				
				throw new IllegalArgumentException("c must be a 2D");
			}
			
			vect = new Vector2D(v1 , v2);
		}
		else {
			vect = new Vector2D();
		}
		
		return vect;
		
	}
	
	public Double tieneDataDoub(JSONObject data, String aux) {
		Double doub = null;
		
		if(data.has(aux)) {
			doub = data.getDouble(aux);
		}
		else {
			doub = 9.81;
		}
		
		return doub;
	}
	
	
	@Override
	public JSONObject getInfoData() {
		JSONObject j = new JSONObject();
		j.put("c1", "the first point towards bodies move ( a json list of 2 numbers, e.g., [100.0,50.0]");
		j.put("c2", "the second point towards bodies move ( a json list of 2 numbers, e.g., [100.0,50.0]");
		j.put("g1", "the length of the first acceleration vector (a number)");
		j.put("g2", "the length of the first acceleration vector (a number)");
		return j;
	}

}
