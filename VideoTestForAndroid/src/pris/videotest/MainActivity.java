package pris.videotest;

import java.io.ByteArrayOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.ShutterCallback;
import android.hardware.Camera.Size;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends Activity implements SurfaceHolder.Callback {

	private Camera mCamera;// Camera����
	private Button mButton;// �Ҳ����򣬵����������ͼ�����գ����¼�
	private SurfaceView mSurfaceView;// ��ʾͼ���surfaceView
	private SurfaceHolder holder;// SurfaceView�Ŀ�����
	private AutoFocusCallback mAutoFocusCallback = new AutoFocusCallback();// AutoFocusCallback�Զ��Խ��Ļص�����
	private ImageView sendImageIv;// ����ͼƬ��imageview��λ���Ҳ�����

	private String strCaptureFilePath = Environment
			.getExternalStorageDirectory() + "/DCIM/Camera/";// ����ͼ���·��
	private boolean ifInit;
	private int screenWidth;
	private int screenHeight;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		if (checkCameraHardware(this)) {
			Log.e("============", "����ͷ����");// ��֤����ͷ�Ƿ����
		}
		/* ����״̬�� */
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		//��Ļ����
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		/* ���ر����� */
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		/* �趨��Ļ��ʾΪ���� */
		// this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

		setContentView(R.layout.activity_main);// ----------------------

        screenWidth = 640;  
        screenHeight = 480; 
		/* SurfaceHolder���� */
		mSurfaceView = (SurfaceView) findViewById(R.id.surface);
		holder = mSurfaceView.getHolder();
		holder.addCallback(this);
		holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		/* ��������Button��OnClick�¼����� */

		mButton = (Button) findViewById(R.id.btn);
		mButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				/* �Զ��Խ������� */
				// mCamera.autoFocus(mAutoFocusCallback);// ����mCamera��
				 //takePicture();
				ifRefresh = true;
				ifInit = true;
			}
		});

		sendImageIv = (ImageView) findViewById(R.id.imageView);

		Button socketTestBtn = (Button) findViewById(R.id.socketTestBtn);
		socketThread = new SocketThread();
		socketTestBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				new Thread(socketThread).start();
			}
		});

	}

	// ///////----------��дSurfaceHolder.Callback�ӿڵķ�����
	// �ڴ�������ʱ����õķ���
	@Override
	public void surfaceCreated(SurfaceHolder surfaceholder) {

		ifInit = true;
		initCamera();
//		try {
//			mCamera = null;
//			try {
//				mCamera = Camera.open(0);// ��������ڵͰ汾�ֻ��open�����������߼��汾����˷����������Ǿ��д򿪶��
//				// ������������������������Ϊ������ı��
//				// ��manifest���趨����С�汾��Ӱ�����﷽���ĵ��ã������С�汾�趨���󣨰汾���ͣ�����ide�ｫ����������вε�
//				// open����;
//				// ���ģ�����汾�ϸߵĻ����޲ε�open����������nullֵ!���Ծ���ʹ��ͨ�ð汾��ģ������API��
//			} catch (Exception e) {
//				Log.e("============", "����ͷ��ռ��");
//			}
//			if (mCamera == null) {
//				Log.e("============", "�����Ϊ��");
//				System.exit(0);
//			}
//			mCamera.setPreviewDisplay(holder);// ������ʾ��������
//			priviewCallBack pre = new priviewCallBack();// ����Ԥ���ص�����
//			mCamera.setPreviewCallback(pre); // ����Ԥ���ص�����
//			// mCamera.getParameters().setPreviewFormat(ImageFormat.JPEG);
//			mCamera.startPreview();// ��ʼԤ�����ⲽ��������Ҫ
//		} catch (IOException exception) {
//			mCamera.release();
//			mCamera = null;
//		}

		// �������ʾ���Ĵ��룺
		/*
		 * ������� mCamera = null; try { mCamera = Camera.open(0); } catch
		 * (Exception e) { Log.e("============", "����ͷ��ռ��"); } if (mCamera ==
		 * null) { Log.e("============", "���ؽ��Ϊ��"); System.exit(0); } //
		 * mCamera.setPreviewDisplay(holder); priviewCallBack pre = new
		 * priviewCallBack(); mCamera.setPreviewCallback(pre); Log.w("wwwwwwww",
		 * mCamera.getParameters().getPreviewFormat() + "");
		 * mCamera.startPreview();
		 */
	}

	// �����ı��ʱ����õķ���
	@Override
	public void surfaceChanged(SurfaceHolder surfaceholder, int format, int w,
			int h) {
		/* �����ʼ�� */
//		initCamera();
	}

	// �������ʱ�ķ���
	@Override
	public void surfaceDestroyed(SurfaceHolder surfaceholder) {
//		stopCamera();
//		mCamera.release();
//		mCamera = null;
		 // ���camera��Ϊnull ,�ͷ�����ͷ  
        if (mCamera != null) {  
            if (isPreview)  
                mCamera.stopPreview();  
            mCamera.release();  
            mCamera = null;  
        }  
        System.exit(0); 
	}

	/* ���յ�method */
	private void takePicture() {
		if (mCamera != null) {
			mCamera.takePicture(shutterCallback, rawCallback, jpegCallback);
		}
	}

	private ShutterCallback shutterCallback = new ShutterCallback() {
		public void onShutter() {
			/* ���¿���˲����������ĳ��� */
		}
	};

	private PictureCallback rawCallback = new PictureCallback() {
		public void onPictureTaken(byte[] _data, Camera _camera) {
			/* Ҫ����raw data?д?�� */
		}
	};

	// ��takepicture�е��õĻص�����֮һ������jpeg��ʽ��ͼ��
	private PictureCallback jpegCallback = new PictureCallback() {
		public void onPictureTaken(byte[] _data, Camera _camera) {

			
			 if (Environment.getExternalStorageState().equals(
			 Environment.MEDIA_MOUNTED)) // �ж�SD���Ƿ���ڣ����ҿ��Կ��Զ�д 
				 {
				 System.out.println("sd�������ҿɶ�д");
			  } else { 
				  System.out.println("sd������");
			  }
			 
			// Log.w("============", _data[55] + "");

			try {
				/* ȡ����Ƭ */
				Bitmap bm = BitmapFactory.decodeByteArray(_data, 0,
						_data.length);
				sendImageIv.setImageBitmap(bm);
//				/* �����ļ� */
//				File myCaptureFile = new File(strCaptureFilePath, "1.jpg");
//				BufferedOutputStream bos = new BufferedOutputStream(
//						new FileOutputStream(myCaptureFile));
//				/* ����ѹ��ת������ */
//				bm.compress(Bitmap.CompressFormat.JPEG, 100, bos);
//
//				/* ����flush()����������BufferStream */
//				bos.flush();
//
//				/* ����OutputStream */
//				bos.close();

				/* ����Ƭ��ʾ3������������ */
				// Thread.sleep(2000);
				/* �����趨Camera */
				stopCamera();
				initCamera();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	};
	public boolean ifRefresh = false;
	private boolean isPreview = false; // �Ƿ���Ԥ����
	private int i = 0;
	private Bitmap bitmapForshow;
	private SocketThread socketThread;

	/* �Զ���class AutoFocusCallback */
	public final class AutoFocusCallback implements
			android.hardware.Camera.AutoFocusCallback {
		public void onAutoFocus(boolean focused, Camera camera) {

			/* �Ե��������� */
			if (focused) {
//				takePicture();
			}
		}
	};

	/* �����ʼ����method */
	private void initCamera() {
//		if (mCamera != null) {
//			try {
//				Camera.Parameters parameters = mCamera.getParameters();
//				/*
//				 * �趨��Ƭ��СΪ1024*768�� ��ʽΪJPG
//				 */
//				// parameters.setPictureFormat(PixelFormat.JPEG);
//				parameters.setPictureSize(1024, 768);
//				mCamera.setParameters(parameters);
//				/* ��Ԥ������ */
//				mCamera.startPreview();
//			} catch (Exception e) {
//				e.printStackTrace();
//			}
//		}
		if (!isPreview ) {  
            mCamera = Camera.open(0);  
        }  
        if (mCamera != null && !isPreview) {  
            try {  
                Camera.Parameters parameters = mCamera.getParameters();  
                parameters.setPreviewSize(screenWidth, screenHeight); // ����Ԥ����Ƭ�Ĵ�С  
                parameters.setPreviewFpsRange(20, 30); // ÿ����ʾ20~30֡  
                parameters.setPictureFormat(ImageFormat.NV21); // ����ͼƬ��ʽ  
                parameters.setPictureSize(screenWidth, screenHeight); // ������Ƭ�Ĵ�С  
                // camera.setParameters(parameters); // android2.3.3�Ժ���Ҫ���д���  
                mCamera.setPreviewDisplay(holder); // ͨ��SurfaceView��ʾȡ������  
                mCamera.setPreviewCallback(new priviewCallBack()); // ���ûص�����  
                mCamera.startPreview(); // ��ʼԤ��  
                mCamera.autoFocus(null); // �Զ��Խ�  
            } catch (Exception e) {  
                e.printStackTrace();  
            }  
            isPreview = true;  
        } 
	}

	/* ֹͣ�����method */
	private void stopCamera() {
		if (mCamera != null) {
			try {
				/* ֹͣԤ�� */
				mCamera.stopPreview();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	// �������ͷ�Ƿ���ڵ�˽�з���
	private boolean checkCameraHardware(Context context) {
		if (context.getPackageManager().hasSystemFeature(
				PackageManager.FEATURE_CAMERA)) {
			// ����ͷ����
			return true;
		} else {
			// ����ͷ������
			return false;
		}
	}

	// ÿ��cam�ɼ�����ͼ��ʱ���õĻص�������ǰ���Ǳ��뿪��Ԥ��
	class priviewCallBack implements Camera.PreviewCallback {

		@Override
		public void onPreviewFrame(byte[] data, Camera camera) {
			// TODO Auto-generated method stub
			// Log.w("wwwwwwwww", data[5] + "");
			// Log.w("֧�ָ�ʽ", mCamera.getParameters().getPreviewFormat()+"");
			if (ifRefresh) {
				ifRefresh = false;
				decodeToBitMap(data, camera);
				ifRefresh = true;
			}

		}
	}

	public void decodeToBitMap(byte[] data, Camera _camera) {
		Size size = mCamera.getParameters().getPreviewSize();
		try {
			long currentTimeMillis = System.currentTimeMillis();
//			YuvImage image = new YuvImage(data, ImageFormat.NV21, size.width,
//					size.height, null);
//			// Log.w("wwwwwwwww", size.width + " " + size.height);
//			if (image != null) {
//				ByteArrayOutputStream stream = new ByteArrayOutputStream();
//				image.compressToJpeg(new Rect(0, 0, size.width, size.height),
//						80, stream);
//				Bitmap bmp = BitmapFactory.decodeByteArray(
//						stream.toByteArray(), 0, stream.size());
//				sendImageIv.setImageBitmap(bmp);
				int width = size.width;
				int height = size.height;
//				int[] pixels = new int[width * height];
//				bmp.getPixels(pixels, 0, width, 0, 0, width, height);
//				System.out.println("red " + Color.red(pixels[0]));
//				System.out.println("green " + Color.green(pixels[0]));
//				System.out.println("blue " + Color.blue(pixels[0]));
//				System.out.println("alpha " + Color.alpha(pixels[0]));
				
//				int i = JNIClient.helloAndroid(pixels, width, height);
//				System.out.println(i);
				if (ifInit) {
					//if (JNIClient.init(data, width, height))
//					if (JNIClient.initShift(pixels, width, height))
					//if(JNIClient.initVIBE(pixels, width, height))
					if(JNIClient.initWithByte(data, width, height))
						ifInit = false;
				}
				
//				if (JNIClient.detect(data, width, height) && !ifInit) {
//					sendImageIv.setBackgroundColor(Color.RED);
//					System.out.println(System.currentTimeMillis()-currentTimeMillis);
//					i++;
//				}else {
//					sendImageIv.setBackgroundColor(Color.BLUE);
//				}
//				if (JNIClient.detectWithShift(pixels, width, height) && !ifInit) {
				if (JNIClient.detectWithByte(data, width, height) && !ifInit) {
					sendImageIv.setBackgroundColor(Color.RED);
					socketThread.write(data);
					i++;
					System.out.println(System.currentTimeMillis()-currentTimeMillis);
				}else {
					sendImageIv.setBackgroundColor(Color.BLUE);
				}
				//int[] result = JNIClient.detectWithReturn(pixels, width, height);
				//int[] result = JNIClient.detectWithVIBE(pixels, width, height);
				//bitmapForshow = Bitmap.createBitmap(result, 40, 30, Config.RGB_565);
				//sendImageIv.setImageBitmap(bitmapForshow);
				
				// Log.w("wwwwwwwww", bmp.getWidth() + " " + bmp.getHeight());
				// Log.w("wwwwwwwww",
				// (bmp.getPixel(100, 100) & 0xff) + "  "
				// + ((bmp.getPixel(100, 100) >> 8) & 0xff) + "  "
				// + ((bmp.getPixel(100, 100) >> 16) & 0xff));
//				image=null;
//				bmp.recycle();
//				pixels =null;
//				stream.close();
				System.gc();
//			}
		} catch (Exception ex) {
			Log.e("Sys", "Error:" + ex.getMessage());
		}
	}

	static {
		System.loadLibrary("VideoTest");
	}

}
