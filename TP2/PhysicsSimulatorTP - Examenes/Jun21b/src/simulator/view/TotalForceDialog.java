package simulator.view;

import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.table.DefaultTableModel;

import org.json.JSONArray;
import org.json.JSONObject;

import simulator.control.Controller;
import simulator.model.BodiesGroup;
import simulator.model.Body;
import simulator.model.SimulatorObserver;

public class TotalForceDialog extends JDialog implements SimulatorObserver{
	

	private DefaultTableModel _dataTableModel;
	private Controller _ctrl;
	private List<JSONObject> _forceLawsInfo;
	private String[] _headers = { "Body", "Total Forces"};
	
	private ArrayList<String> bodiesDisp;
	private JPanel opciones;
	private JButton cancel;
	private JTable t;
	
	
	private int _status = 0;
	
	

	TotalForceDialog(Frame parent, Controller ctrl) {
		super(parent, true);
		_ctrl = ctrl;
		initGUI();
		_ctrl.addObserver(this);
		
		bodiesDisp = new ArrayList<String>();
		}

	private void initGUI() {
		
		setTitle("Total Force per Body");
		
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		setContentPane(mainPanel);
		
		JPanel botones = new JPanel();
		botones.setAlignmentX(CENTER_ALIGNMENT);
		
		
		
		// tabla
		
		_dataTableModel = new DefaultTableModel(_headers, 0) {
			

		};

		_dataTableModel.setColumnIdentifiers(_headers);
		t = new JTable(_dataTableModel);
		
		
		t.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		t.setFillsViewportHeight(true);
		JScrollPane scrollPane = new JScrollPane(t);
		mainPanel.add(scrollPane);
		mainPanel.add(botones);
		
		
		// opcion Ok
		
		opciones = new JPanel();
		opciones.setAlignmentX(CENTER_ALIGNMENT);
		mainPanel.add(opciones);
		
		cancel = new JButton("Ok");
		cancel.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				_status = 0;
				setVisible(false);	
			}
		});
		opciones.add(cancel);

		setPreferredSize(new Dimension(700, 400));
		pack();
		setResizable(false);
		setVisible(false);
	}
	
	public void open() {
		
		if (bodiesDisp.size() == 0)
			return;
		
		setLocationRelativeTo(getParent());
		
		pack();
		setVisible(true);
		//return;
	}

	

	@Override
	public void onAdvance(Map<String, BodiesGroup> groups, double time) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onReset(Map<String, BodiesGroup> groups, double time, double dt) {
		bodiesDisp.clear();
	}

	@Override
	public void onRegister(Map<String, BodiesGroup> groups, double time, double dt) {
		
		for(BodiesGroup g: groups.values()) {
			for(Body b : g) {
				bodiesDisp.add(b.getId());
			}
		}
	}

	@Override
	public void onGroupAdded(Map<String, BodiesGroup> groups, BodiesGroup g) {
		
	}

	@Override
	public void onBodyAdded(Map<String, BodiesGroup> groups, Body b) {
		bodiesDisp.add(b.getId());
	}

	@Override
	public void onDeltaTimeChanged(double dt) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onForceLawsChanged(BodiesGroup g) {
		// TODO Auto-generated method stub
		
	}
}