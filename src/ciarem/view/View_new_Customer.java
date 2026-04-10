package ciarem.view;

import java.awt.*;
import java.text.ParseException;
import java.time.LocalDate;

import javax.swing.*;
import javax.swing.text.MaskFormatter;

import raven.datetime.DatePicker;

public class View_new_Customer extends JDialog {
	private boolean upd = false;
	private static final long serialVersionUID = 1L;
	private JTextField Fld_id, Fld_name, Fld_phone, Cntr_dob;
	private DatePicker Fld_dob;
	private JButton Btn_submit;
	GridBagConstraints gbc;
	MaskFormatter idMask, phoneMask;
	
	public View_new_Customer(JFrame parent) {
		super(parent, "New Customer", true);
		setTitle("Dashboard");
		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setLayout(new BorderLayout());
		
		init();
		
		setMinimumSize(new Dimension(400,300));
		pack();
		setResizable(false);
		setLocationRelativeTo(parent);
	}
	
	public View_new_Customer(JFrame parent, String id, String name, String phone, LocalDate dob) {
		this(parent);
		
		upd = true;
		Fld_id.setText(id);
		Fld_name.setText(name);
		Fld_phone.setText(phone);
		Fld_dob.setSelectedDate(dob);
		
		Fld_id.setEditable(false);
		Btn_submit.setText("Update Customer");
	}
	
	private void init() {
	
		try {
			idMask = new MaskFormatter("############");
			phoneMask = new MaskFormatter("##########");
		} catch (ParseException e) {
			e.printStackTrace();
		}
	
		JLabel Lbl_title = new JLabel("Add a Customer", JLabel.CENTER),
			Lbl_id = new JLabel("Aadhar Number"),
			Lbl_name = new JLabel("Full Name"),
			Lbl_phone = new JLabel("Contact Number"),
			Lbl_dob = new JLabel("Date of Birth");
		
		Font f = new Font("SansSerif", Font.BOLD, 28);
		Lbl_title.setFont(f);
		
		JPanel Pnl_main = new JPanel(new GridBagLayout());
		gbc = new GridBagConstraints();
		gbc.insets = new Insets(10,10,10,10);
		
		Fld_id = new JFormattedTextField(idMask); 
		Fld_name = new JTextField();
		Fld_phone = new JFormattedTextField(phoneMask);
		Cntr_dob = new JFormattedTextField();
		Fld_dob = new DatePicker();
		
		Fld_id.setHorizontalAlignment(JTextField.CENTER);
		Fld_name.setHorizontalAlignment(JTextField.CENTER);
		Fld_phone.setHorizontalAlignment(JTextField.CENTER);
		Fld_dob.setEditor((JFormattedTextField) Cntr_dob);
		Fld_dob.setDateSelectionMode(DatePicker.DateSelectionMode.SINGLE_DATE_SELECTED);
	
		Btn_submit = new JButton("Add Customer");
	
		addToPanel(Pnl_main, Lbl_id, 0, 0, GridBagConstraints.NONE, 0.0);
		addToPanel(Pnl_main, Fld_id, 0, 1, GridBagConstraints.HORIZONTAL, 1.0);
		addToPanel(Pnl_main, Lbl_name, 1, 0, GridBagConstraints.NONE, 0.0);
		addToPanel(Pnl_main, Fld_name, 1, 1, GridBagConstraints.HORIZONTAL, 1.0);
		addToPanel(Pnl_main, Lbl_phone, 2, 0, GridBagConstraints.NONE, 0.0);
		addToPanel(Pnl_main, Fld_phone, 2, 1, GridBagConstraints.HORIZONTAL, 1.0);
		addToPanel(Pnl_main, Lbl_dob, 3, 0, GridBagConstraints.NONE, 0.0);
		addToPanel(Pnl_main, Cntr_dob, 3, 1, GridBagConstraints.HORIZONTAL, 1.0);
	
		add(Lbl_title,BorderLayout.NORTH);
		add(Pnl_main,BorderLayout.CENTER);
		add(Btn_submit,BorderLayout.SOUTH);
	}
	
	
	private void addToPanel(JPanel jp, JComponent c, int gridy, int gridx, int fill, double weightx) {
		gbc.gridy = gridy;
		gbc.gridx = gridx;
		gbc.fill = fill;
		gbc.weightx = weightx;
		if(c instanceof JLabel) { gbc.anchor = GridBagConstraints.WEST; }
		else { gbc.anchor = GridBagConstraints.CENTER; }
		jp.add(c, gbc);
	}
	
	public boolean getMode() { return upd; }
	
	public String getId() { return Fld_id.getText(); }
	
	public String getName() { return Fld_name.getText(); }
	
	public String getPhone() { return Fld_phone.getText(); }
	
	public LocalDate getDob() { return Fld_dob.getSelectedDate(); }
	
	public JButton getBtnSubmit() { return Btn_submit; }
	
	
	
	public void killView() {
		upd = false;
		Fld_id.setText("");
		Fld_name.setText("");
		Fld_phone.setText("");
		Fld_dob.setSelectedDate(LocalDate.now());

		Fld_id.setEditable(true);
		Btn_submit.setText("Add Customer");
		
		this.dispose();
	}
	
}
