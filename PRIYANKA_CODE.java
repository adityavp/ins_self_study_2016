import javax.swing.JOptionPane;

public class Authentication
{
	public static void main(String args[])
	{
		JOptionPane.showConfirmDialog(null,"Confirm?");
		String correctname="tanes";

		String uname=JOptionPane.showInputDialog("Enter user name:");
		if(uname.equalsIgnoreCase(correctname))
			System.out.println("Welcome"+uname);
		else
			System.out.println("Fail Authentication");
	}
}