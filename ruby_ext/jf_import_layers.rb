
if RUBY_PLATFORM[/mingw/]  && Sketchup.is_64bit?

   require "#{File.dirname(__FILE__)}/jf_import_layers/#{RUBY_VERSION}/x64/JF_ImportLayers"

   module JF
      module ImportLayers

         menu = defined?(JF.menu) ? JF.menu : UI.menu
         menu.add_item("Import Layers") { main }

         def self.main
            file = UI.openpanel("Select SketchUp Model", nil, "*.skp")
            if file && File.exists?(file)
               info = get_layer_info(file)
               Sketchup.active_model.start_operation("Import Layers", true)
               info.each {|name, color|
                  layer = Sketchup.active_model.layers.add(name)
                  layer.color = color
               }
               Sketchup.active_model.commit_operation
            end
         end
      end

   end

end
