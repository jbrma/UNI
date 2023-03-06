package simulator.factories;

import org.json.JSONObject;

import simulator.misc.Vector2D;
import simulator.model.ForceLaws;
import simulator.model.MovingTowardsFixedPoint;

public class MovingTowardsFixedPointBuilder extends Builder<ForceLaws>{

	protected Vector2D c;
	protected double g;
	
	public MovingTowardsFixedPointBuilder() {
		super("mtfp", "Moving Towards Fixed Point");
		
	}

	@Override
	protected ForceLaws createInstance(JSONObject data) {
		
		ForceLaws f;
		
		if(data.has("c") && data.has("g")) {
			
			double v1 = data.getJSONArray("c").getDouble(0);
			double v2 = data.getJSONArray("c").getDouble(1);

			if(data.getJSONArray("c").length() > 2) {
				
				throw new IllegalArgumentException("c must be a 2D");
			}
			
			
			this.c = new Vector2D(v1 , v2);
			this.g = data.getDouble("g");
		     
		    f = new MovingTowardsFixedPoint(c, g);
		    
		}
		else {
			
			this.c = new Vector2D();
			
			f = new MovingTowardsFixedPoint(c, 9.81);
		}
	
		return f;
	}

}
