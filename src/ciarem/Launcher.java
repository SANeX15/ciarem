package ciarem;

import javax.swing.*;
import com.formdev.flatlaf.FlatLightLaf;

import ciarem.ctrl.Ctrl_Dashboard;
import ciarem.dao.DBHelper;
import ciarem.view.*;

public class Launcher {
	public static void main(String[] args) {
		DBHelper.init();
		try {
			UIManager.setLookAndFeel(new FlatLightLaf());
		} catch (UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
		SwingUtilities.invokeLater(() -> start());
	}
	public static void start() {
		View_Dashboard vD = new View_Dashboard();
		Ctrl_Dashboard cD = new Ctrl_Dashboard(vD);
	}
}