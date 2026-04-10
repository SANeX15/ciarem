package ciarem;

import javax.swing.*;
import com.formdev.flatlaf.FlatLightLaf;
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
		SwingUtilities.invokeLater(() -> {
			new View_Dashboard();
		});
	}
}