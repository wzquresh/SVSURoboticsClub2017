class Bump{
	private:
		int bumpPin;
		XYCoordinate local_postion;

	public:
		Bump(int sensorID, long local_x, long local_y);
		bool getValue();
		XYCoordinate GetPosition();
};
