class Square {
public:
	Square( int width );
	void Render();
	void Click( int x, int y );
	void Drag( int x, int y );
	void WindowWidth( int w, int h );
	void ToggleTexturing();
	int texid;
};