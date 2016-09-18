VALUE import_layers() {

	std::string model_name{ "C:\\Users\\Jim\\model.skp" };
	SUResult res{ SU_ERROR_NONE };
	SUInitialize();
	SUModelRef model = SU_INVALID;
		
	res = SUModelCreateFromFile(&model, model_name.c_str());
	_ASSERTE(res == SU_ERROR_NONE);
	
	// Get layer count from model
	size_t layers_in_model{ 0 };
	res = SUModelGetNumLayers(model, &layers_in_model);
	_ASSERTE(res == SU_ERROR_NONE);
	_RPT1(0, "layers_in_model: %d\n", layers_in_model);

	std::vector<SULayerRef> layers(layers_in_model);
	size_t layers_returned = 0;

	res = SUModelGetLayers(model, layers_in_model, &layers[0], &layers_returned);
	_ASSERTE(res == SU_ERROR_NONE);

	SUStringRef layer_name = SU_INVALID;
	res = SUStringCreate(&layer_name);
	_ASSERTE(res == SU_ERROR_NONE);

	// a Ruby Array to return to SketchUp Ruby
	VALUE layer_names = rb_ary_new();
	VALUE layer_hash = rb_hash_new();
	SUMaterialRef material = SU_INVALID;
	SUColor color;
	
	for (std::vector<SULayerRef>::size_type i = 0; i != layers.size(); i++) {
		// Get name from Layer
		res = SULayerGetName(layers[i], &layer_name);
		_ASSERTE(res == SU_ERROR_NONE);
		size_t name_length = 0;
		res = SUStringGetUTF8Length(layer_name, &name_length);
		_ASSERTE(res == SU_ERROR_NONE);
		char* name_utf8 = new char[name_length + 1];
		res = SUStringGetUTF8(layer_name, name_length + 1, name_utf8, &name_length);
		_ASSERTE(res == SU_ERROR_NONE);
		_RPT1(0, "layer_name: >%s<\n", name_utf8);
		//rb_ary_push(layer_names, rb_str_new2(name_utf8));
		
		// Get Material from Layer
		res = SULayerGetMaterial(layers[i], &material);
		_ASSERTE(SUIsValid(material));
		_ASSERTE(res == SU_ERROR_NONE);

		// Get Color from Material
		res = SUMaterialGetColor(material, &color);
		_ASSERTE(res == SU_ERROR_NONE);

		VALUE color_ary = rb_ary_new();
		rb_ary_push(color_ary, INT2FIX(color.red));
		rb_ary_push(color_ary, INT2FIX(color.green));
		rb_ary_push(color_ary, INT2FIX(color.blue));
		rb_ary_push(color_ary, INT2FIX(color.alpha));

		rb_hash_aset(layer_hash, rb_str_new2(name_utf8), color_ary);

		delete[]name_utf8;
	}
	SUStringRelease(&layer_name);
	SUModelRelease(&model);
	SUTerminate();
	//return layer_names;
	return layer_hash;
}