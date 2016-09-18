VALUE import_layers() {
	std::string model_name{ "C:\\Users\\Jim\\model.skp" };
	SUResult res{ SU_ERROR_NONE };
	SUInitialize();
	SUModelRef model = SU_INVALID;
		
	res = SUModelCreateFromFile(&model, model_name.c_str());
	_RPT1(0, "SUModelCreateFromFile: %d\n", res);
	
	// Get layer count from model
	size_t layers_in_model{ 0 };
	res = SUModelGetNumLayers(model, &layers_in_model);
	_RPT1(0, "SUModelGetNumLayers: %d\n", res);
	_RPT1(0, "layers_in_model: %d\n", layers_in_model);

	std::vector<SULayerRef> layers(layers_in_model);
	size_t layers_returned = 0;

	res = SUModelGetLayers(model, layers_in_model, &layers[0], &layers_returned);
	_RPT1(0, "SUModelGetLayers: %d\n", res);

	SUStringRef layer_name = SU_INVALID;
	res = SUStringCreate(&layer_name);
	_RPT1(0, "SUStringCreate: %d\n", res);

	// a Ruby Array to return to SketchUp Ruby
	VALUE layer_names = rb_ary_new();

	for (std::vector<SULayerRef>::size_type i = 0; i != layers.size(); i++) {
		res = SULayerGetName(layers[i], &layer_name);
		_RPT1(0, "SULayerGetName: %d\n", res);
		size_t name_length = 0;
		res = SUStringGetUTF8Length(layer_name, &name_length);
		_RPT1(0, "SUStringGetUTF8Length: %d\n", res);
		char* name_utf8 = new char[name_length + 1];
		res = SUStringGetUTF8(layer_name, name_length + 1, name_utf8, &name_length);
		_RPT1(0, "SUStringGetUTF8: %d\n", res);
		_RPT1(0, "layer_name: >%s<\n", name_utf8);
		rb_ary_push(layer_names, rb_str_new2(name_utf8));
		delete[]name_utf8;
	}
	SUStringRelease(&layer_name);
	SUModelRelease(&model);
	SUTerminate();
	return layer_names;
}