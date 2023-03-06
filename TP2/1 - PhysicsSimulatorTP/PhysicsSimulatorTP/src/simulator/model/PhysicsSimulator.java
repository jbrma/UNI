package simulator.model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;

public class PhysicsSimulator {

	 	private double timePerStep;
	    private ForceLaws forceLaws;
	    private Map<String, BodiesGroup> groups;
	    private double currentTime;
	
	public PhysicsSimulator(ForceLaws _forceLaws, double _timePerStep) {
		 if (_timePerStep <= 0) {
	            throw new IllegalArgumentException("Time per step must be positive");
	        }
	     if (_forceLaws == null) {
	            throw new IllegalArgumentException("Force laws cannot be null");
	        }
	        this.timePerStep = _timePerStep;
	        this.forceLaws = _forceLaws;
	        this.groups = new HashMap<>();
	        this.currentTime = 0;
	        
	}

	public void advance() {
        for (BodiesGroup group : groups.values()) {
            group.advance(timePerStep);
        }
        currentTime += timePerStep;
    }

    public void addGroup(String id) {
        if (groups.containsKey(id)) {
            throw new IllegalArgumentException("Group with id " + id + " already exists");
        }
        BodiesGroup group = new BodiesGroup(id, forceLaws);
        groups.put(id, group);
    }

    public void addBody(Body b) {
        String groupId = b.getgId();
        if (!groups.containsKey(groupId)) {
            throw new IllegalArgumentException("Group with id " + groupId + " does not exist");
        }
        BodiesGroup group = groups.get(groupId);
        group.addBody(b);
    }

    public void setForceLaws(String id, ForceLaws fl) {
        if (!groups.containsKey(id)) {
            throw new IllegalArgumentException("Group with id " + id + " does not exist");
        }
        BodiesGroup group = groups.get(id);
        group.setForceLaws(fl);
    }

    public JSONObject getState() {
        JSONObject state = new JSONObject();
        state.put("time", currentTime);

        ArrayList<String> groupIds = new ArrayList<>(groups.keySet());
        JSONArray groupStates = new JSONArray();
        for (String groupId : groupIds) {
            groupStates.put(groups.get(groupId).getState());
        }

        state.put("groups", groupStates);
        return state;
    }

    @Override
    public String toString() {
        return getState().toString();
    }
}
