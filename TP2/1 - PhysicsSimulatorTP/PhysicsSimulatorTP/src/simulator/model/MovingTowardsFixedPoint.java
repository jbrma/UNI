package simulator.model;

import java.util.List;

import simulator.misc.*;

public class MovingTowardsFixedPoint implements ForceLaws{

	private double g;
	private Vector2D c;
	
	public MovingTowardsFixedPoint(Vector2D _c, double _g) {
		
		if(_c == null) {
			throw new IllegalArgumentException("c value is null");
		}
		if(_g <= 0) {
			throw new IllegalArgumentException("g value is non-positive");
		}
		this.c = _c;
		this.g = _g;
	}
	
	@Override
	public void apply(List<Body> bs) {
		
		Vector2D dir = new Vector2D().direction(); // Direccion auxiliar c - pi
		
		for(int i = 0; i < bs.size(); i++) {
			
			 dir = c.minus(bs.get(i).getPosition().direction());
			 bs.get(i).addForce(dir.scale(bs.get(i).getMass() * this.g));
		}
	}
}
