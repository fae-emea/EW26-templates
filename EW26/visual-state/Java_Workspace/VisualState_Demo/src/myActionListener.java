import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;


// ********************
// Action listeners
// ********************
public class myActionListener implements ActionListener
{
	private main_window mw;
	
	public myActionListener (main_window mw)
	{
		this.mw = mw;
	}

	public void actionPerformed(ActionEvent e)
	{
		try
		{
			JButton button = (JButton)e.getSource();

			// but1 button
			if (button == mw.but1_button)
			{
				mw.event_queue.add(System1.eButton1);
			}

			// but2 button
			if (button == mw.but2_button)
			{
				mw.event_queue.add(System1.eButton2);
			}
			
			// exit button
			if (button == mw.exit_button)
			{
				mw.exit_routine();
			}
		}

		catch (Exception ex)
		{
			JOptionPane.showMessageDialog(null, "ActionListener \n"+ex.getMessage() + "\n");
		}
	}
}