// Prints the user settings directory this Ghidra installation uses (it depends on
// XDG_CONFIG_HOME, the user name and the release name), for installing extensions into it.
// Run with the java source launcher: java -cp <Utility.jar>:<Generic.jar> SettingsDir.java
public class SettingsDir {
	public static void main(String[] args) throws Exception {
		System.out.println(new ghidra.GhidraApplicationLayout().getUserSettingsDir());
	}
}
