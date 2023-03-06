package simulator.model;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

public class BodiesGroup {

	private String id;
    private ForceLaws forceLaws;
    private List<Body> bodies;
    
	public BodiesGroup(String _id, ForceLaws _forceLaws) {
		
		if (_id == null || _forceLaws == null) {
            throw new IllegalArgumentException("id or forceLaws are null");
        }
        if (_id.trim().length() == 0) {
            throw new IllegalArgumentException("id must contain at least one non-blank character");
        }
        this.id = _id;
        this.forceLaws = _forceLaws;
        this.bodies = new ArrayList<>();
	}

		public String getId() {
	        return id;
	    }

	    public void setForceLaws(ForceLaws fl) {
	        if (fl == null) {
	            throw new IllegalArgumentException("ForceLaws cannot be null.");
	        }
	        this.forceLaws = fl;
	    }

	    public void addBody(Body b) {
	        if (b == null) {
	            throw new IllegalArgumentException("Body cannot be null.");
	        }
	        if (bodies.stream().anyMatch(body -> body.getId().equals(b.getId()))) {
	            throw new IllegalArgumentException("A body with the same id already exists in the group.");
	        }
	        bodies.add(b);
	    }

	    void advance(double dt) {
	        if (dt <= 0) {
	            throw new IllegalArgumentException("Time step must be positive.");
	        }
	        bodies.forEach(Body::resetForce);
	        forceLaws.apply(bodies);
	        bodies.forEach(body -> body.advance(dt));
	    }

	    public JSONObject getState() {
	        JSONArray bodiesJson = new JSONArray();
	        bodies.forEach(body -> bodiesJson.put(body.getState()));
	        JSONObject stateJson = new JSONObject();
	        stateJson.put("id", id);
	        stateJson.put("bodies", bodiesJson);
	        return stateJson;
	    }

	    @Override
	    public String toString() {
	        return getState().toString();
	    }
	
}
