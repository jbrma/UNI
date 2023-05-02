package simulator.model;

import java.util.List;

import simulator.misc.Vector2D;

public class MovingTowardsTwoFixedPoints implements ForceLaws{


	private double g1, g2;
	private Vector2D c1, c2;
	
	public MovingTowardsTwoFixedPoints(Vector2D _c1, Vector2D _c2, double _g1, double _g2) {
		
		if(_c1 == null || _c2 == null) {
			throw new IllegalArgumentException("any c value is null");
		}
		if(_g1 <= 0 || _g2 <= 0) {
			throw new IllegalArgumentException("any g value is non-positive");
		}
		this.c1 = _c1;
		this.c2 = _c2;
		this.g1 = _g1;
		this.g2 = _g2;
	}
	
	@Override
	public void apply(List<Body> bs) {
		
		Vector2D dir1 = new Vector2D().direction(); // Direccion auxiliar c1 - pi
		Vector2D dir2 = new Vector2D().direction(); // Direccion auxiliar c2 - pi
		
		
		for(Body b : bs) {

			 dir1 = c1.minus(b.getPosition().direction());
			 dir2 = c2.minus(b.getPosition().direction());
			 
			 b.addForce(((dir1.scale(g1)).plus(dir2.scale(g2))).scale(b.getMass()));
			 
		}
	}
	
	public String toString() {
		
		return "Moving towards " + c1 + "," + c2 + " with constant acceleration " + g1 + "," + g2;
	}
}
