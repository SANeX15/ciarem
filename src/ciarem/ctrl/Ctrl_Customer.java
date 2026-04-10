package ciarem.ctrl;

import javax.swing.JOptionPane;

import ciarem.dao.DAO_Customer;
import ciarem.view.View_new_Customer;
import ciarem.mdl.Mdl_Customer;

public class Ctrl_Customer {
	private DAO_Customer dao;
	private View_new_Customer view;
	
	public Ctrl_Customer(DAO_Customer dao, View_new_Customer view) {
		this.dao = dao;
		this.view = view;
		initCtrl();
	}
	
	private void initCtrl() {
		view.getBtnSubmit().addActionListener(e -> saveCustomer());
	}
	
	private void saveCustomer() {
		// save their data, i mean
		boolean status = false;
		Mdl_Customer customer;
		if (InputValidator.isAadharValid(view.getId()) &&
			InputValidator.isNameValid(view.getName()) &&
			InputValidator.isDobValid(view.getDob()) &&
			InputValidator.isPhoneValid(view.getPhone())) {
			
			customer = new Mdl_Customer(view.getId(),view.getName(), view.getPhone(), view.getDob());
		}
		else {
			JOptionPane.showMessageDialog(null, "Wrong Values are entered.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
		if (!view.getMode()) { status = dao.create(customer); }
		else { status = dao.update(customer); }
		
		if (status) {
			view.killView();
			JOptionPane.showMessageDialog(null, "The new Customer is registered.", "Success", JOptionPane.INFORMATION_MESSAGE);
		}
		else {
			JOptionPane.showMessageDialog(null, "Failed to register new Customer.", "Error", JOptionPane.ERROR_MESSAGE);
		}
	}
}
